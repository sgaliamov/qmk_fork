// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// GPIO pin driving the layer-indicator LED.
#define LED_INDICATOR_PIN GP17

// Layer indices.
enum layers {
    _BASE,  // Ergonomic (default)
    _FN,    // Function / shortcut
    _QWERTY // Standard QWERTY
};

// Tap dance indices for Alt/Ctrl modifier keys:
//   single hold      → hold the base modifier
//   double-tap+hold  → hold Shift + base modifier
enum tap_dances {
    TD_LALT,
    TD_LCTL,
    TD_RCTL,
    TD_RALT,
};

// TEMP_EN: right-side key on _QWERTY — temporarily switch the OS IME to
// English and reveal _BASE for the duration of the hold, then switch back.
enum custom_keycodes {
    TEMP_EN = QK_USER,
};

// Pressing both Shift keys simultaneously (held) toggles _BASE <-> _QWERTY.
enum combo_events {
    BOTH_SFT,
};

const uint16_t PROGMEM both_sft_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[] = {
    [BOTH_SFT] = COMBO_ACTION(both_sft_combo),
};

// Require hold (not tap) so quick Shift presses aren't delayed.
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* _BASE – Ergonomic layout (default) */
    [_BASE] = LAYOUT(
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      XXXXXXX,    XXXXXXX,            XXXXXXX,    XXXXXXX,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F12,     KC_PGUP,
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_F10,     XXXXXXX,            XXXXXXX,    KC_F11,     KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_PGDN,
        KC_COMM,    KC_DOT,     KC_M,       KC_S ,      KC_P,       KC_Q,       KC_PAUS,    XXXXXXX,            XXXXXXX,    KC_LBRC,    KC_RBRC,    KC_Y,       KC_T,       KC_W,       KC_Q,       KC_COMM,
        KC_TAB,     KC_L,       KC_R,       KC_R,       KC_R,       KC_D,       KC_SLSH,    KC_BSLS,            KC_INS,     KC_QUOT,    KC_L,       KC_N,       KC_T,       KC_N,       KC_B,       KC_EQL,
        KC_DEL,     KC_X,       KC_X,       KC_W,       KC_V,       KC_SCLN,    KC_HOME,    KC_END,             KC_BSLS,    KC_SCLN,    KC_B,       KC_L,       KC_Y,       KC_DOT,     KC_J,       KC_BSPC,
        KC_LALT,    MO(_FN),    KC_APP,     KC_LCMD,    KC_LCTL,    KC_SPC,     KC_LSFT,    KC_ENT,             TD(TD_RALT),KC_RSFT,    KC_SPC,     TD(TD_RCTL),KC_LEFT,    KC_UP,      KC_DOWN,    KC_RGHT,

    ),

    /* _FN – Function / shortcut layer */
    [_FN] = LAYOUT(
        TO(_BASE),  _______,    _______,    _______,    _______,    _______,    XXXXXXX,    XXXXXXX,            XXXXXXX,    XXXXXXX,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    KC_P1,      KC_P2,      KC_P3,      KC_P4,      KC_P5,      XXXXXXX,    XXXXXXX,            XXXXXXX,    XXXXXXX,    KC_P6,      KC_P7,      KC_P8,      KC_P9,      KC_P0,      _______,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PSCR,    XXXXXXX,            XXXXXXX,    KC_NUM,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PCMM,
        KC_PMNS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_MPLY,    XXXXXXX,            _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PAST,    KC_PPLS,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,            _______,    KC_PSLS,    XXXXXXX,    XXXXXXX,    KC_PDOT,    XXXXXXX,    XXXXXXX,    _______,
        _______,    TO(_BASE),  _______,    _______,    _______,    _______,    _______,    _______,            TO(_BASE),  _______,    _______,    KC_PEQL,    _______,    _______,    _______,    _______,
    ),

    /* _QWERTY – Standard QWERTY layout */
    [_QWERTY] = LAYOUT(
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      XXXXXXX,    XXXXXXX,            XXXXXXX,    XXXXXXX,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F12,     KC_PGUP,
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_F10,     XXXXXXX,            XXXXXXX,    KC_F11,     KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_PGDN,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_PAUS,    XXXXXXX,            XXXXXXX,    KC_CAPS,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_COMM,
        KC_MINS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_LBRC,    KC_RBRC,            _______,    KC_QUOT,    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_EQL,
        KC_DEL,     KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       _______,    _______,            _______,    KC_SLSH,    KC_N,       KC_M,       KC_DOT,     KC_UP,      KC_RGHT,    KC_BSPC,
        KC_LALT,    MO(_FN),    KC_APP,     KC_LCMD,    KC_LCTL,    KC_SPC,     KC_LSFT,    KC_ENT,             MO(_FN),    KC_RSFT,    KC_SPC,     KC_ENT,     KC_LEFT,    KC_UP,      KC_DOWN,    KC_RGHT,
    ),
};

// clang-format on

// ---------------------------------------------------------------------------
// Modifier tap dance (Alt / Ctrl)
//   single tap  → send modifier once
//   single hold → hold modifier
//   double tap  → send modifier twice
//   double hold → hold Shift + modifier
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
    uint16_t       base_kc;          // Bare modifier keycode (Alt or Ctrl)
    uint8_t        shift_base_mods;  // Modifier mask for Shift+base
    bool           suspended_qwerty; // QWERTY was suspended for this hold
} mod_td_user_data_t;

static mod_td_user_data_t lctl_td_data = {MOD_TD_NONE, KC_LCTL, MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL), false};
static mod_td_user_data_t rctl_td_data = {MOD_TD_NONE, KC_RCTL, MOD_BIT(KC_RSFT) | MOD_BIT(KC_RCTL), false};
static mod_td_user_data_t lalt_td_data = {MOD_TD_NONE, KC_LALT, MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT), false};
static mod_td_user_data_t ralt_td_data = {MOD_TD_NONE, KC_RALT, MOD_BIT(KC_RSFT) | MOD_BIT(KC_RALT), false};

static mod_td_state_t resolve_mod_td(tap_dance_state_t *state) {
    if (state->count == 1) return state->pressed ? MOD_TD_SINGLE_HOLD : MOD_TD_SINGLE_TAP;
    if (state->count == 2) return state->pressed ? MOD_TD_DOUBLE_HOLD : MOD_TD_DOUBLE_TAP;
    return MOD_TD_NONE;
}

// ---------------------------------------------------------------------------
// QWERTY-layer suspension (reference-counted)
// When a non-Shift modifier (Ctrl, Alt) or MO1 key is held while _QWERTY is
// active, temporarily revert to _BASE so shortcut key positions match the
// ergonomic layout.  Shift is intentionally excluded: it must stay on _QWERTY
// so the user can type capital letters in the active language.
// Multiple modifiers held simultaneously are handled correctly because the
// counter is only decremented to zero when the last modifier is released.
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
void mod_td_finished(tap_dance_state_t *state, void *user_data) {
    mod_td_user_data_t *td = (mod_td_user_data_t *)user_data;
    td->state              = resolve_mod_td(state);
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
            register_mods(td->shift_base_mods);
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
            unregister_mods(td->shift_base_mods);
            break;
        default:
            break;
    }
    resume_qwerty(td->suspended_qwerty);
    td->suspended_qwerty = false;
    td->state            = MOD_TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LALT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lalt_td_data},
    [TD_LCTL] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lctl_td_data},
    [TD_RCTL] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rctl_td_data},
    [TD_RALT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &ralt_td_data},
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

// MO(_FN) — left key on _QWERTY and both keys on _BASE.
// While _QWERTY is active, suspend it so _FN shortcuts resolve to ergonomic
// _BASE positions.  A press counter handles both physical keys held at once.
//
// TEMP_EN — right key on _QWERTY only.
// Sends Win+Space to ask the OS to switch the IME to English, then suspends
// _QWERTY so _BASE (ergonomic English layout) is accessible for the hold
// duration.  Sends Win+Space again on release to restore the original IME.
// Shift is NOT suspended by either key: Shift+letter must produce the
// capitalised character of the active language.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Tracks how many MO(_FN) physical keys are currently held.
    static uint8_t mo_fn_hold_count = 0;
    // True while _QWERTY is suspended due to an MO(_FN) hold.
    static bool mo_fn_suspended = false;
    // True while _QWERTY is suspended due to a TEMP_EN hold.
    static bool temp_en_suspended = false;

    switch (keycode) {
        case MO(_FN):
            if (record->event.pressed) {
                // First key down suspends QWERTY; subsequent presses just count.
                if (mo_fn_hold_count == 0) {
                    mo_fn_suspended = suspend_qwerty();
                }
                mo_fn_hold_count++;
            } else {
                // Restore QWERTY only after the last MO(_FN) key is released.
                if (mo_fn_hold_count > 0) mo_fn_hold_count--;
                if (mo_fn_hold_count == 0) {
                    resume_qwerty(mo_fn_suspended);
                    mo_fn_suspended = false;
                }
            }
            return true; // let QMK handle the actual layer activation

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
    }
    return true;
}
