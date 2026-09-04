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
    TD_LSFT, // base: LSFT, double-hold combo: LALT + LSFT
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
    BOTH_SFT_TD,
    BOTH_SFT_PLAIN,
};

const uint16_t PROGMEM both_sft_td_combo[]    = {TD(TD_LSFT), TD(TD_RSFT), COMBO_END};
const uint16_t PROGMEM both_sft_plain_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[] = {
    [BOTH_SFT_TD]    = COMBO_ACTION(both_sft_td_combo),
    [BOTH_SFT_PLAIN] = COMBO_ACTION(both_sft_plain_combo),
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
        KC_TAB,      KC_Q,        KC_B,        KC_C,        KC_U,        KC_Y,        KC_CAPS,     XXXXXXX,             XXXXXXX,     KC_PAUS,     KC_DOT,      KC_F,        KC_O,        KC_Z,        KC_SCLN,     LBRC_SWAP,
        KC_ENT,      KC_L,        KC_R,        KC_E,        KC_A,        KC_D,        KC_SLSH,     KC_HOME,             KC_PGUP,     QUOT_SWAP,   KC_S,        KC_T,        KC_I,        KC_N,        KC_H,        KC_ENT,
        KC_DEL,      KC_COMM,     KC_V,        KC_W,        KC_G,        KC_X,        KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      KC_J,        KC_M,        KC_K,        KC_P,        KC_UP,       KC_BSPC,
        KC_BSLS,     TD(TD_LALT), KC_APP,      KC_LCMD,     TD(TD_RCTL), KC_SPC,      TD(TD_LSFT), MO(_FN),             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     TD(TD_LALT), KC_DOWN
    ),

    [_QWERTY] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      TEMP_EN,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_CAPS,     XXXXXXX,             XXXXXXX,     KC_PAUS,     KC_Y,        KC_U,        KC_I,        KC_O,        KC_SCLN,     KC_LBRC,
        KC_ENT,      KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_SLSH,     KC_HOME,             KC_PGUP,     KC_QUOT,     KC_H,        KC_J,        KC_K,        KC_L,        KC_P,        KC_ENT,
        KC_DEL,      KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_UP,       KC_BSPC,
        KC_BSLS,     KC_LALT,     KC_APP,      KC_LCMD,     KC_LCTL,     KC_SPC,      KC_LSFT,     MO(_FN),             KC_INS,      KC_RSFT,     KC_SPC,      KC_RCTL,     KC_LEFT,     KC_RGHT,     KC_RALT,     KC_DOWN
    ),

    [_FN] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_TAB,      KC_MPLY,     KC_MPRV,     KC_MNXT,     XXXXXXX,     XXXXXXX,     TD_TOGGLE,   XXXXXXX,             XXXXXXX,     KC_NUM,      KC_PDOT,     KC_P1,       KC_P2,       KC_P3,       KC_SCLN,     KC_LBRC,
        KC_PEQL,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     ARROW_THIN,  KC_PSLS,     KC_HOME,             KC_PGUP,     KC_QUOT,     XXXXXXX,     KC_P4,       KC_P5,       KC_P6,       KC_P0,       KC_PENT,
        KC_DEL,      KC_PCMM ,    XXXXXXX,     XXXXXXX,     XXXXXXX,     ARROW_FAT,   KC_PMNS,     KC_END,              KC_PGDN,     KC_PPLS,     KC_PAST,     KC_P7,       KC_P8,       KC_P9,       KC_UP,       KC_BSPC,
        KC_BSLS,     TD(TD_LALT), KC_APP,      KC_LCMD,     TD(TD_RCTL), KC_SPC,      TD(TD_LSFT), MO(_FN),             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     TD(TD_LALT), KC_DOWN
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
    mod_td_state_t state;      // Resolved gesture
    uint16_t       base_kc;    // Base modifier keycode for tap / hold
    uint8_t        combo_mods; // Modifier mask for the double-hold combo
    bool           reveals;    // When bypassed on QWERTY, the plain hold also reveals _BASE
} mod_td_user_data_t;

static mod_td_user_data_t rctl_td_data = {MOD_TD_NONE, KC_RCTL, MOD_BIT(KC_RSFT) | MOD_BIT(KC_RCTL), true};
static mod_td_user_data_t lsft_td_data = {MOD_TD_NONE, KC_LSFT, MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), false};
static mod_td_user_data_t rsft_td_data = {MOD_TD_NONE, KC_RSFT, MOD_BIT(KC_LALT) | MOD_BIT(KC_RSFT), false};
static mod_td_user_data_t lalt_td_data = {MOD_TD_NONE, KC_LALT, MOD_BIT(KC_LALT) | MOD_BIT(KC_RCTL), true};

static mod_td_state_t resolve_mod_td(tap_dance_state_t *state) {
    if (state->count == 1) return state->pressed ? MOD_TD_SINGLE_HOLD : MOD_TD_SINGLE_TAP;
    if (state->count == 2) return state->pressed ? MOD_TD_DOUBLE_HOLD : MOD_TD_DOUBLE_TAP;
    return MOD_TD_NONE;
}

// ---------------------------------------------------------------------------
// QWERTY layer management (derived state, position-tracked holds)
//
// qwerty_selected is the single source of truth for which base layout the
// user has chosen; it is toggled only by the both-Shift combo.  Keys whose
// hold temporarily reveals _BASE (Ctrl/Alt, TEMP_EN) are tracked in a small
// table keyed by MATRIX POSITION, so a release always matches its press even
// if the layer (and thus the resolved keycode) changed mid-hold.  The actual
// layer is always recomputed from this state, never patched incrementally,
// which makes the system self-healing.
// ---------------------------------------------------------------------------
static bool qwerty_selected = false;

typedef struct {
    keypos_t key;        // Matrix position of the held key
    uint16_t unreg_kc;   // Keycode we registered ourselves (KC_NO if QMK core handles it)
    bool     reveals;    // Hold reveals _BASE while _QWERTY is selected
    bool     ime_toggle; // Send Win+Space again on release (TEMP_EN)
    bool     consume;    // Press was consumed, so consume the release too
    bool     active;
} qwerty_hold_t;

#define MAX_QWERTY_HOLDS 8
static qwerty_hold_t qwerty_holds[MAX_QWERTY_HOLDS];

static qwerty_hold_t *find_qwerty_hold(keypos_t key) {
    for (uint8_t i = 0; i < MAX_QWERTY_HOLDS; i++) {
        if (qwerty_holds[i].active && qwerty_holds[i].key.row == key.row && qwerty_holds[i].key.col == key.col) {
            return &qwerty_holds[i];
        }
    }
    return NULL;
}

// Recompute the layer from the current state: _QWERTY is on iff it is the
// selected layout and no revealing key is held.
static void apply_qwerty_layer(void) {
    bool reveal = false;
    for (uint8_t i = 0; i < MAX_QWERTY_HOLDS; i++) {
        if (qwerty_holds[i].active && qwerty_holds[i].reveals) {
            reveal = true;
            break;
        }
    }
    bool want_qwerty = qwerty_selected && !reveal;
    if (want_qwerty != IS_LAYER_ON(_QWERTY)) {
        if (want_qwerty) {
            layer_on(_QWERTY);
        } else {
            layer_off(_QWERTY);
        }
    }
}

// Records a hold WITHOUT applying the layer change. Callers that consume the
// event (return false) must call apply_qwerty_layer() themselves right after;
// callers that let QMK resolve the key normally (return true) must NOT call
// it here — see the big comment on process_record_user/post_process_record_user
// for why the timing matters.
static void add_qwerty_hold(keypos_t key, uint16_t unreg_kc, bool reveals, bool ime_toggle, bool consume) {
    qwerty_hold_t *slot = find_qwerty_hold(key); // reuse a stale slot for the same position
    if (!slot) {
        for (uint8_t i = 0; i < MAX_QWERTY_HOLDS; i++) {
            if (!qwerty_holds[i].active) {
                slot = &qwerty_holds[i];
                break;
            }
        }
    }
    if (!slot) return;
    slot->key        = key;
    slot->unreg_kc   = unreg_kc;
    slot->reveals    = reveals;
    slot->ime_toggle = ime_toggle;
    slot->consume    = consume;
    slot->active     = true;
}

// Called when the tap-dance term expires or a non-TD key is pressed.
// Resolves the gesture and either taps or holds the modifier.
// Layer handling lives entirely in process_record_user / apply_qwerty_layer;
// these callbacks only manage modifier registration.
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
// Unregisters held modifiers.
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
    td->state = MOD_TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lsft_td_data},
    [TD_RSFT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rsft_td_data},
    [TD_LALT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lalt_td_data},
    [TD_RCTL] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rctl_td_data},
};

// Toggle the selected layout (_BASE <-> _QWERTY) when both Shift keys are held
// simultaneously — either the tap-dance pair on _BASE/_FN or the plain pair on
// _QWERTY.  Also sends Win+Space to switch the OS input method (e.g. IME).
void process_combo_event(uint16_t combo_index, bool pressed) {
    if ((combo_index == BOTH_SFT_TD || combo_index == BOTH_SFT_PLAIN) && pressed) {
        qwerty_selected = !qwerty_selected;
        apply_qwerty_layer();
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
// TEMP_EN — sends Win+Space to ask the OS to switch the IME to English, then
// reveals _BASE (ergonomic English layout) for the hold duration.  Sends
// Win+Space again on release to restore the original IME.
//
// Left Ctrl / Left Alt — when held while _QWERTY is selected, they reveal
// _BASE so Ctrl/Alt shortcuts resolve to the ergonomic key positions.  This
// keeps shortcuts identical across layouts (e.g. while typing Russian on
// _QWERTY, Ctrl+C stays on the same physical key as on _BASE).
//
// Shift never reveals _BASE: Shift+letter must produce the capitalised
// character of the active language.
//
// Tap-dance modifiers — while _QWERTY is the selected layout, tap dance is
// bypassed entirely: the TD keys reachable through _FN or the revealed _BASE
// act as instant plain modifiers (Ctrl/Alt ones also reveal _BASE).  Tap
// dance stays fully functional when _BASE is the selected layout.
//
// All holds are tracked by matrix position (see qwerty_holds), so a release
// is always paired with its press even when the layer — and therefore the
// resolved keycode — changed between the two events.
//
// IMPORTANT timing note: QMK resolves a PRESS event's own action (register
// the key/mod) in process_record_handler(), which runs AFTER this function
// returns — but store_or_get_action() recomputes the layer fresh on every
// press (it only uses the cached layer on release). So if we change the
// _QWERTY layer bit *before* returning `true` here, THIS SAME keypress gets
// re-resolved against the new layer instead of the one it was actually
// pressed on. Ctrl/Alt therefore record their hold here but defer the actual
// apply_qwerty_layer() call to post_process_record_user(), which runs after
// this key's own action has already been resolved. Handlers that fully
// consume the event (`return false`) never reach post-process, so they must
// call apply_qwerty_layer() themselves, synchronously, right here.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        qwerty_hold_t *hold = find_qwerty_hold(record->event.key);
        if (hold) {
            bool consume = hold->consume;
            if (hold->unreg_kc != KC_NO) {
                unregister_code(hold->unreg_kc);
            }
            bool ime_toggle = hold->ime_toggle;
            hold->active    = false;
            apply_qwerty_layer();
            if (ime_toggle) {
                tap_code16(LGUI(KC_SPC)); // switch the OS IME back
            }
            return !consume;
        }
    }

    switch (keycode) {
        case TEMP_EN:
            if (record->event.pressed) {
                // Switch OS IME to English, then reveal _BASE for typing.
                tap_code16(LGUI(KC_SPC));
                add_qwerty_hold(record->event.key, KC_NO, true, true, true);
                apply_qwerty_layer(); // event is fully consumed below: apply now
            }
            return false;

        case KC_LCTL:
        case KC_LALT:
            // Holding Ctrl/Alt reveals _BASE while _QWERTY is selected so
            // shortcuts use the ergonomic key positions. The layer change is
            // deferred to post_process_record_user (see note above) so this
            // very keypress still resolves to plain Ctrl/Alt.
            if (record->event.pressed) {
                add_qwerty_hold(record->event.key, KC_NO, true, false, false);
            }
            return true; // let QMK register/unregister the modifier itself

        case TD(TD_LSFT):
        case TD(TD_RSFT):
        case TD(TD_LALT):
        case TD(TD_RCTL):
            // QWERTY selected: no tap dance — act as an instant plain
            // modifier; Ctrl/Alt additionally reveal _BASE for the hold.
            if (record->event.pressed && qwerty_selected) {
                mod_td_user_data_t *td = (mod_td_user_data_t *)tap_dance_actions[TD_INDEX(keycode)].user_data;
                register_code(td->base_kc);
                add_qwerty_hold(record->event.key, td->base_kc, td->reveals, false, true);
                apply_qwerty_layer(); // event is fully consumed below: apply now
                return false;
            }
            return true; // _BASE selected: normal tap-dance handling

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

// Runs after process_record_handler() has already resolved and executed this
// key's own action. Safe point to apply any layer change requested above for
// events that returned `true` (e.g. Ctrl/Alt reveal), without perturbing the
// resolution of the key that triggered it.
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    apply_qwerty_layer();
}
