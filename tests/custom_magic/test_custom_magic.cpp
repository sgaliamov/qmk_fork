// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"

extern "C" {
#include "custom_magic.h"
}

using testing::_;
using testing::InSequence;

class CustomMagic : public TestFixture {
   protected:
    enum { BASE, QWERTY, FN };

    void SetUp() override {
        custom_magic_reset();
        for (uint8_t layer = BASE; layer <= FN; ++layer) {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                    add_key(physical_key(layer, row, col));
                }
            }
        }
    }

    KeymapKey physical_key(uint8_t layer, uint8_t row, uint8_t col) {
        return KeymapKey(layer, col, row, custom_magic_keycode(layer, row, col));
    }

    void toggle_tap_dance() {
        auto fn      = physical_key(BASE, 5, 1);
        bool fn_held = layer_state_is(FN);
        if (!fn_held) {
            fn.press();
            run_one_scan_loop();
        }
        tap_key(physical_key(FN, 2, 6));
        if (!fn_held) {
            fn.release();
            run_one_scan_loop();
        }
    }

    void switch_layout(TestDriver &driver) {
        InSequence sequence;
        EXPECT_REPORT(driver, (KC_LGUI));
        EXPECT_REPORT(driver, (KC_LGUI, KC_SPC));
        EXPECT_REPORT(driver, (KC_LGUI));
        EXPECT_EMPTY_REPORT(driver);
        tap_combo({physical_key(BASE, 5, 6), physical_key(BASE, 5, 9)}, COMBO_HOLD_TERM + 2);
        VERIFY_AND_CLEAR(driver);
    }

    void expect_quiet(TestDriver &driver) {
        EXPECT_NO_REPORT(driver);
        idle_for(TAPPING_TERM + COMBO_TERM + 1);
        VERIFY_AND_CLEAR(driver);
    }
};

struct Modifier {
    uint8_t  layer;
    uint8_t  col;
    uint16_t base;
    uint16_t extra;

    bool is_shift() const {
        return base == KC_LSFT || base == KC_RSFT;
    }
};

class CustomMagicModifier : public CustomMagic, public testing::WithParamInterface<Modifier> {
   protected:
    void enter_layer() {
        if (GetParam().layer == FN) {
            physical_key(BASE, 5, 1).press();
            run_one_scan_loop();
        }
    }

    void leave_layer() {
        if (GetParam().layer == FN) {
            physical_key(BASE, 5, 1).release();
            run_one_scan_loop();
        }
    }
};

TEST_P(CustomMagicModifier, DisabledPressReleaseAndRepeatedTapsHaveNoDanceDelay) {
    TestDriver driver;
    auto       mod = GetParam();
    auto       key = physical_key(mod.layer, 5, mod.col);
    EXPECT_NO_REPORT(driver);
    toggle_tap_dance();
    enter_layer();
    VERIFY_AND_CLEAR(driver);

    for (unsigned i = 0; i < 3; ++i) {
        EXPECT_REPORT(driver, (mod.base));
        key.press();
        run_one_scan_loop();
        if (mod.is_shift()) {
            idle_for(COMBO_TERM + 1);
        }
        VERIFY_AND_CLEAR(driver);

        EXPECT_EMPTY_REPORT(driver);
        key.release();
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
    }
    leave_layer();
    expect_quiet(driver);
}

TEST_P(CustomMagicModifier, BypassedHoldReleasesAfterReenablingAndLeavingFn) {
    TestDriver driver;
    auto       mod = GetParam();
    auto       key = physical_key(mod.layer, 5, mod.col);
    toggle_tap_dance();
    enter_layer();

    EXPECT_REPORT(driver, (mod.base));
    key.press();
    idle_for(mod.is_shift() ? COMBO_TERM + 2 : 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    toggle_tap_dance();
    leave_layer();
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    expect_quiet(driver);
}

TEST_P(CustomMagicModifier, ReenabledSingleAndDoubleHoldsKeepOriginalGestures) {
    TestDriver driver;
    auto       mod = GetParam();
    auto       key = physical_key(mod.layer, 5, mod.col);
    toggle_tap_dance();
    toggle_tap_dance();
    enter_layer();

    EXPECT_NO_REPORT(driver);
    key.press();
    idle_for(COMBO_TERM + 2);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (mod.base));
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EMPTY_REPORT(driver);
    key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_NO_REPORT(driver);
    tap_key(key);
    key.press();
    idle_for(COMBO_TERM + 2);
    VERIFY_AND_CLEAR(driver);
    EXPECT_REPORT(driver, (mod.base, mod.extra));
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);
    EXPECT_EMPTY_REPORT(driver);
    key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    leave_layer();
    expect_quiet(driver);
}

TEST_P(CustomMagicModifier, ReenabledSingleAndDoubleTapsKeepOriginalGestures) {
    TestDriver driver;
    auto       mod = GetParam();
    auto       key = physical_key(mod.layer, 5, mod.col);
    toggle_tap_dance();
    toggle_tap_dance();
    enter_layer();

    for (unsigned taps = 1; taps <= 2; ++taps) {
        EXPECT_NO_REPORT(driver);
        for (unsigned i = 0; i < taps; ++i) {
            tap_key(key);
        }
        VERIFY_AND_CLEAR(driver);
        {
            InSequence sequence;
            for (unsigned i = 0; i < taps; ++i) {
                EXPECT_REPORT(driver, (mod.base));
                EXPECT_EMPTY_REPORT(driver);
            }
            idle_for(TAPPING_TERM + COMBO_TERM + 1);
            VERIFY_AND_CLEAR(driver);
        }
    }
    leave_layer();
    expect_quiet(driver);
}

INSTANTIATE_TEST_CASE_P(PhysicalModifiers, CustomMagicModifier, testing::Values(Modifier{0, 0, KC_LALT, KC_RCTL}, Modifier{0, 4, KC_RCTL, KC_RSFT}, Modifier{0, 6, KC_LSFT, KC_LALT}, Modifier{0, 9, KC_RSFT, KC_LALT}, Modifier{0, 11, KC_RCTL, KC_RSFT}, Modifier{0, 15, KC_LALT, KC_RCTL}, Modifier{2, 0, KC_LALT, KC_RCTL}, Modifier{2, 4, KC_RCTL, KC_RSFT}, Modifier{2, 6, KC_LSFT, KC_LALT}, Modifier{2, 9, KC_RSFT, KC_LALT}, Modifier{2, 11, KC_RCTL, KC_RSFT}));

TEST_F(CustomMagic, DisabledBothShiftStillSwitchesLayoutsAndIme) {
    TestDriver driver;
    toggle_tap_dance();
    switch_layout(driver);
    EXPECT_TRUE(layer_state_is(QWERTY));
    EXPECT_TRUE(custom_magic_led_state());
    switch_layout(driver);
    EXPECT_FALSE(layer_state_is(QWERTY));
    EXPECT_FALSE(custom_magic_led_state());
    expect_quiet(driver);
}

TEST_F(CustomMagic, DisablingPendingDancePreservesItsRelease) {
    TestDriver driver;
    auto       alt = physical_key(BASE, 5, 0);
    auto       fn  = physical_key(BASE, 5, 1);
    fn.press();
    run_one_scan_loop();

    EXPECT_NO_REPORT(driver);
    alt.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    EXPECT_REPORT(driver, (KC_LALT));
    toggle_tap_dance();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    alt.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    fn.release();
    run_one_scan_loop();
    expect_quiet(driver);
}

TEST_F(CustomMagic, DisablingActiveDoubleHoldReleasesBothModifiers) {
    TestDriver driver;
    auto       alt = physical_key(BASE, 5, 0);
    tap_key(alt);
    alt.press();
    EXPECT_REPORT(driver, (KC_LALT, KC_RCTL));
    idle_for(TAPPING_TERM + 2);
    VERIFY_AND_CLEAR(driver);
    EXPECT_NO_REPORT(driver);
    toggle_tap_dance();
    VERIFY_AND_CLEAR(driver);
    EXPECT_EMPTY_REPORT(driver);
    alt.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
    expect_quiet(driver);
}

TEST_F(CustomMagic, QwertyPlainAndBypassedModifiersPreserveRevealAndRelease) {
    TestDriver driver;
    switch_layout(driver);

    for (bool disabled : {false, true}) {
        if (disabled) {
            toggle_tap_dance();
        }
        for (auto col : {0, 4}) {
            auto key  = physical_key(QWERTY, 5, col);
            auto base = col == 0 ? KC_LALT : KC_LCTL;
            EXPECT_REPORT(driver, (base));
            key.press();
            run_one_scan_loop();
            VERIFY_AND_CLEAR(driver);
            EXPECT_FALSE(layer_state_is(QWERTY));

            auto ctrl = physical_key(BASE, 5, 11);
            EXPECT_REPORT(driver, (base, KC_RCTL));
            ctrl.press();
            run_one_scan_loop();
            VERIFY_AND_CLEAR(driver);
            EXPECT_REPORT(driver, (KC_RCTL));
            key.release();
            run_one_scan_loop();
            VERIFY_AND_CLEAR(driver);
            EXPECT_FALSE(layer_state_is(QWERTY));
            EXPECT_EMPTY_REPORT(driver);
            ctrl.release();
            run_one_scan_loop();
            VERIFY_AND_CLEAR(driver);
            EXPECT_TRUE(layer_state_is(QWERTY));
        }

        auto fn = physical_key(QWERTY, 5, 1);
        fn.press();
        run_one_scan_loop();
        for (auto col : {0, 4, 6, 9}) {
            auto key   = physical_key(FN, 5, col);
            auto base  = col == 0 ? KC_LALT : col == 4 ? KC_RCTL : col == 6 ? KC_LSFT : KC_RSFT;
            bool shift = col == 6 || col == 9;
            EXPECT_REPORT(driver, (base));
            key.press();
            idle_for(shift ? COMBO_TERM + 2 : 1);
            VERIFY_AND_CLEAR(driver);
            EXPECT_EQ(layer_state_is(QWERTY), shift);
            EXPECT_EMPTY_REPORT(driver);
            key.release();
            run_one_scan_loop();
            VERIFY_AND_CLEAR(driver);
            EXPECT_TRUE(layer_state_is(QWERTY));
        }
        fn.release();
        run_one_scan_loop();
        expect_quiet(driver);
    }
    switch_layout(driver);
}
