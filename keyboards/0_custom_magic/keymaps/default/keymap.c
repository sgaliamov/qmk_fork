// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// GPIO pin driving the layer-indicator LED.
#define LED_INDICATOR_PIN GP17

// Layer indices.
// _FN is the highest-priority layer so a held MO(_FN) is never shadowed by the
// opaque _QWERTY layer; QMK then resolves it natively with no extra code.
enum layers {
    _BASE,   // Ergonomic (default)
    _QWERTY, // Standard QWERTY
    _FN      // Function / shortcut (highest priority)
};

// Tap dance indices for custom modifier keys:
//   tap / hold       → send or hold the base modifier
//   double-tap+hold  → hold the configured modifier combo
enum tap_dances {
    TD_RSFT, // base: RSFT, double-hold combo: LALT + RSFT
    TD_LALT, // base: LALT, double-hold combo: LALT + RCTL
    TD_RCTL, // base: RCTL, double-hold combo: RSFT + RCTL
};

// TEMP_EN: right-side key on _QWERTY — temporarily switch the OS IME to
// English and reveal _BASE for the duration of the hold, then switch back.
enum custom_keycodes {
    TEMP_EN = QK_USER,
    ARROW_FAT,  // =>
    ARROW_THIN, // ->
    QUOT_SWAP,  // _BASE: " when unshifted, ' when shifted
    LBRC_SWAP,  // _BASE: { when unshifted, [ when shifted
    RBRC_SWAP,  // _BASE: } when unshifted, ] when shifted
    TD_TOGGLE,  // toggles the custom modifier tap-dance behavior on/off
};

// Pressing both Shift keys simultaneously (held) toggles _BASE <-> _QWERTY.
enum combo_events {
    BOTH_SFT,
};

const uint16_t PROGMEM both_sft_combo[] = {KC_LSFT, TD(TD_RSFT), COMBO_END};

combo_t key_combos[] = {
    [BOTH_SFT] = COMBO_ACTION(both_sft_combo),
};

// Require hold (not tap) so quick Shift presses aren't delayed.
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        RBRC_SWAP,
        KC_TAB,      KC_J,        KC_G,        KC_U,        KC_W,        KC_DOT,      KC_CAPS,     XXXXXXX,             XXXXXXX,     KC_PAUS,     KC_B,        KC_M,        KC_O,        KC_F,        KC_COMM,     LBRC_SWAP,
        KC_ENT,      KC_H,        KC_R,        KC_E,        KC_T,        KC_L,        KC_SLSH,     KC_HOME,             KC_PGUP,     QUOT_SWAP,   KC_D,        KC_I,        KC_A,        KC_N,        KC_S,        KC_ENT,
        KC_DEL,      KC_K,        KC_V,        KC_Z,        KC_C,        KC_Y,        KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      KC_X,        KC_P,        KC_Q,        KC_SCLN,     KC_UP,       KC_BSPC,
        KC_BSLS,     TD(TD_LALT), KC_APP,      KC_LCMD,     TD(TD_RCTL), KC_SPC,      TD(TD_RSFT), MO(_FN),             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     TD(TD_LALT), KC_DOWN
    ),

    [_QWERTY] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_CAPS,     XXXXXXX,             XXXXXXX,     KC_PAUS,     KC_Y,        KC_U,        KC_I,        KC_O,        KC_SCLN,     KC_LBRC,
        KC_ENT,      KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_SLSH,     KC_HOME,             KC_PGUP,     KC_QUOT,     KC_H,        KC_J,        KC_K,        KC_L,        KC_P,        KC_ENT,
        KC_DEL,      KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_UP,       KC_BSPC,
        KC_BSLS,     KC_LALT,     KC_APP,      KC_LCMD,     KC_LCTL,     KC_SPC,      KC_LSFT,     MO(_FN),             KC_INS,      KC_RSFT,     KC_SPC,      KC_RCTL,     KC_LEFT,     KC_RGHT,     KC_LALT,     KC_DOWN
    ),

    [_FN] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_P1,       KC_P2,       KC_P3,       KC_P4,       KC_P5,       KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_P6,       KC_P7,       KC_P8,       KC_P9,       KC_P0,       KC_RBRC,
        KC_TAB,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_PDOT,     KC_NUM,      XXXXXXX,             XXXXXXX,     KC_MPLY,     KC_VOLU,     KC_MPRV,     KC_MNXT,     XXXXXXX,     KC_PCMM ,    KC_LBRC,
        KC_PEQL,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_PAST,     KC_PSLS,     KC_HOME,             KC_PGUP,     KC_QUOT,     KC_VOLD,     ARROW_FAT,   ARROW_THIN,  XXXXXXX,     KC_SCLN,     KC_PENT,
        KC_DEL,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     TD_TOGGLE,   KC_PMNS,     KC_END,              KC_PGDN,     KC_PPLS,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_UP,       KC_BSPC,
        KC_BSLS,     TD(TD_LALT), KC_APP,      KC_LCMD,     TD(TD_RCTL), KC_SPC,      TD(TD_RSFT), MO(_FN),             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     TD(TD_LALT), KC_DOWN
    )
};

// clang-format on

// ---------------------------------------------------------------------------
// Modifier tap dance
//   single tap  → send modifier once
//   single hold → hold modifier
//   double tap  → send modifier twice
//   double hold → hold the configured modifier combo
// ---------------------------------------------------------------------------
typedef enum {
    MOD_TD_NONE,
    MOD_TD_SINGLE_TAP,
    MOD_TD_SINGLE_HOLD,
    MOD_TD_DOUBLE_TAP,
    MOD_TD_DOUBLE_HOLD,
} mod_td_state_t;

typedef struct {
    mod_td_state_t state;            // Resolved gesture
    uint16_t       base_kc;          // Base modifier keycode for tap / hold
    uint8_t        combo_mods;       // Modifier mask for the double-hold combo
    bool           suspended_qwerty; // QWERTY was suspended for this hold
} mod_td_user_data_t;

static mod_td_user_data_t rctl_td_data = {MOD_TD_NONE, KC_RCTL, MOD_BIT(KC_RSFT) | MOD_BIT(KC_RCTL), false};
static mod_td_user_data_t rsft_td_data = {MOD_TD_NONE, KC_RSFT, MOD_BIT(KC_LALT) | MOD_BIT(KC_RSFT), false};
static mod_td_user_data_t lalt_td_data = {MOD_TD_NONE, KC_LALT, MOD_BIT(KC_LALT) | MOD_BIT(KC_RCTL), false};

static mod_td_state_t resolve_mod_td(tap_dance_state_t *state) {
    if (state->count == 1) return state->pressed ? MOD_TD_SINGLE_HOLD : MOD_TD_SINGLE_TAP;
    if (state->count == 2) return state->pressed ? MOD_TD_DOUBLE_HOLD : MOD_TD_DOUBLE_TAP;
    return MOD_TD_NONE;
}

// ---------------------------------------------------------------------------
// QWERTY-layer suspension (reference-counted)
// When a tap-dance modifier hold or a plain Ctrl/Alt key is held while _QWERTY
// is active, temporarily revert to _BASE so shortcuts use the ergonomic layout.
// Multiple simultaneous holders are handled correctly because the counter is
// only decremented to zero when the last holder is released.
// ---------------------------------------------------------------------------
static uint8_t qwerty_suspend_count = 0;

// Turn off _QWERTY and increment the suspend counter.
// Returns true if suspension happened (caller stores this to pass resume_qwerty).
static bool suspend_qwerty(void) {
    if (IS_LAYER_ON(_QWERTY) || qwerty_suspend_count > 0) {
        if (qwerty_suspend_count == 0) {
            layer_off(_QWERTY);
        }
        qwerty_suspend_count++;
        return true;
    }
    return false;
}

// Decrement the suspend counter; restore _QWERTY only when the last holder releases.
// was_suspended must be the value returned by the matching suspend_qwerty() call.
static void resume_qwerty(bool was_suspended) {
    if (was_suspended && qwerty_suspend_count > 0) {
        qwerty_suspend_count--;
        if (qwerty_suspend_count == 0) {
            layer_on(_QWERTY);
        }
    }
}

// Called when the tap-dance term expires or a non-TD key is pressed.
// Resolves the gesture and either taps or holds the modifier.
// On hold gestures, suspends _QWERTY so shortcuts use _BASE key positions.
static bool tap_dance_enabled = true;

void mod_td_finished(tap_dance_state_t *state, void *user_data) {
    mod_td_user_data_t *td = (mod_td_user_data_t *)user_data;
    td->state              = resolve_mod_td(state);

    if (!tap_dance_enabled) {
        if (td->state == MOD_TD_DOUBLE_HOLD) {
            td->state = MOD_TD_SINGLE_HOLD;
        }
        switch (td->state) {
            case MOD_TD_SINGLE_TAP:
                tap_code(td->base_kc);
                break;
            case MOD_TD_SINGLE_HOLD:
                register_code(td->base_kc);
                break;
            case MOD_TD_DOUBLE_TAP:
                tap_code(td->base_kc);
                tap_code(td->base_kc);
                break;
            default:
                break;
        }
        return;
    }

    if (td->state == MOD_TD_SINGLE_HOLD || td->state == MOD_TD_DOUBLE_HOLD) {
        td->suspended_qwerty = suspend_qwerty();
    }
    switch (td->state) {
        case MOD_TD_SINGLE_TAP:
            tap_code(td->base_kc);
            break;
        case MOD_TD_SINGLE_HOLD:
            register_code(td->base_kc);
            break;
        case MOD_TD_DOUBLE_TAP:
            tap_code(td->base_kc);
            tap_code(td->base_kc);
            break;
        case MOD_TD_DOUBLE_HOLD:
            register_mods(td->combo_mods);
            break;
        default:
            break;
    }
}

// Called when the tap-dance key is released (after mod_td_finished).
// Unregisters held modifiers and restores _QWERTY if it was suspended.
void mod_td_reset(tap_dance_state_t *state, void *user_data) {
    mod_td_user_data_t *td = (mod_td_user_data_t *)user_data;
    switch (td->state) {
        case MOD_TD_SINGLE_HOLD:
            unregister_code(td->base_kc);
            break;
        case MOD_TD_DOUBLE_HOLD:
            unregister_mods(td->combo_mods);
            break;
        default:
            break;
    }
    resume_qwerty(td->suspended_qwerty);
    td->suspended_qwerty = false;
    td->state            = MOD_TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_RSFT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rsft_td_data},
    [TD_LALT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lalt_td_data},
    [TD_RCTL] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rctl_td_data},
};

// Toggle _BASE <-> _QWERTY when both Shift keys are held simultaneously.
// Also sends Win+Space to switch the OS input method (e.g. IME toggle).
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (combo_index == BOTH_SFT && pressed) {
        bool qwerty_active   = IS_LAYER_ON(_QWERTY) || qwerty_suspend_count > 0;
        qwerty_suspend_count = 0;
        layer_move(qwerty_active ? _BASE : _QWERTY);
        tap_code16(LGUI(KC_SPC));
    }
}

// Layer-indicator LED: on when _QWERTY is active, off otherwise.
layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(LED_INDICATOR_PIN, IS_LAYER_ON_STATE(state, _QWERTY));
    return state;
}

// Configure the layer-indicator LED pin as output and ensure it starts off.
void keyboard_post_init_user(void) {
    gpio_set_pin_output(LED_INDICATOR_PIN);
    gpio_write_pin_low(LED_INDICATOR_PIN);
}

// MO(_FN) needs no handling here: _FN is the highest-priority layer, so a held
// MO(_FN) always wins over _QWERTY and QMK resolves it natively.  The two _FN
// positions that differ between _BASE and _QWERTY (the quote key and the right
// thumb key) are pinned in the _FN layout so Fn shortcuts are identical on both
// base layers.
//
// TEMP_EN — right key on _QWERTY only.
// Sends Win+Space to ask the OS to switch the IME to English, then suspends
// _QWERTY so _BASE (ergonomic English layout) is accessible for the hold
// duration.  Sends Win+Space again on release to restore the original IME.
//
// Left Ctrl / Left Alt — when held while _QWERTY is active, they also suspend
// _QWERTY so Ctrl/Alt shortcuts resolve to the ergonomic _BASE key positions.
// This keeps shortcuts identical across layers (e.g. while typing Russian on
// _QWERTY, Ctrl+C stays on the same physical key as on _BASE).
//
// Shift is NOT suspended by these keys: Shift+letter must produce the
// capitalised character of the active language.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // True while _QWERTY is suspended due to a TEMP_EN hold.
    static bool temp_en_suspended = false;
    // True while _QWERTY is suspended due to a Left Ctrl / Left Alt hold.
    static bool lctl_suspended = false;
    static bool lalt_suspended = false;

    switch (keycode) {
        case TEMP_EN:
            if (record->event.pressed) {
                // Switch OS IME to English, then reveal _BASE for typing.
                tap_code16(LGUI(KC_SPC));
                temp_en_suspended = suspend_qwerty();
            } else {
                // Restore _QWERTY, then switch the OS IME back.
                resume_qwerty(temp_en_suspended);
                temp_en_suspended = false;
                tap_code16(LGUI(KC_SPC));
            }
            return false;

        case KC_LCTL:
            // Holding Left Ctrl reveals _BASE while _QWERTY is active so that
            // Ctrl shortcuts use the ergonomic key positions.
            if (record->event.pressed) {
                lctl_suspended = suspend_qwerty();
            } else {
                resume_qwerty(lctl_suspended);
                lctl_suspended = false;
            }
            return true; // let QMK register/unregister the modifier itself

        case KC_LALT:
            // Holding Left Alt reveals _BASE while _QWERTY is active so that
            // Alt shortcuts use the ergonomic key positions.
            if (record->event.pressed) {
                lalt_suspended = suspend_qwerty();
            } else {
                resume_qwerty(lalt_suspended);
                lalt_suspended = false;
            }
            return true; // let QMK register/unregister the modifier itself

        case ARROW_FAT:
            if (record->event.pressed) SEND_STRING("=>");
            return false;

        case ARROW_THIN:
            if (record->event.pressed) SEND_STRING("->");
            return false;

        case QUOT_SWAP:
            // _BASE: swap the shifted/unshifted output of the quote key so an
            // unshifted tap produces " and a shifted tap produces '.
            if (record->event.pressed) {
                uint8_t shift = get_mods() & MOD_MASK_SHIFT;
                if (shift) {
                    unregister_mods(shift);
                    tap_code(KC_QUOT);
                    register_mods(shift);
                } else {
                    tap_code16(S(KC_QUOT));
                }
            }
            return false;

        case LBRC_SWAP:
            // _BASE: swap the shifted/unshifted output of the left bracket key so
            // an unshifted tap produces { and a shifted tap produces [.
            if (record->event.pressed) {
                uint8_t shift = get_mods() & MOD_MASK_SHIFT;
                if (shift) {
                    unregister_mods(shift);
                    tap_code(KC_LBRC);
                    register_mods(shift);
                } else {
                    tap_code16(S(KC_LBRC));
                }
            }
            return false;

        case RBRC_SWAP:
            // _BASE: swap the shifted/unshifted output of the right bracket key so
            // an unshifted tap produces } and a shifted tap produces ].
            if (record->event.pressed) {
                uint8_t shift = get_mods() & MOD_MASK_SHIFT;
                if (shift) {
                    unregister_mods(shift);
                    tap_code(KC_RBRC);
                    register_mods(shift);
                } else {
                    tap_code16(S(KC_RBRC));
                }
            }
            return false;

        case TD_TOGGLE:
            if (record->event.pressed) {
                tap_dance_enabled = !tap_dance_enabled;
            }
            return false;
    }
    return true;
}
