// Copyright 2026 Anzood
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Port of the ZMK Lintilla keymap (lintilla-zmk/config/lintilla.keymap).
// Lintilla's fn keys above the pinky columns moved to the "tucky" thumb keys.

#include QMK_KEYBOARD_H
#include "ws2812.h"

enum layers { DEF, SYM, NAV, NUM, FN, ADJ };

enum custom_keycodes {
    GLOBE = SAFE_RANGE, // Apple Globe (consumer usage "next keyboard layout")
    APP_NEXT,           // Cmd+Tab, Cmd stays held while the layer is held
    APP_PREV,           // Cmd+Shift+Tab, same session as APP_NEXT
    WIN_NEXT,           // Opt+Tab, Opt stays held while the layer is held
};

// Thumb: hold = Hyper (app switching), tap = one-shot Ctrl (Ctrl+C/D/L/S).
// The tap keycode is a placeholder, process_record_user replaces it.
#define HYP MT(MOD_HYPR, KC_F24)

// Layer mods: hold = ordinary mod (for arrows/digits), tap = one-shot mod
// for the next key after the layer is released. Tap-preferred.
#define SMOD(mod) MT(mod, KC_F23)

#define HY(kc) HYPR(kc)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Visual rows (left half | right half):
     *   1: outer home, top row        2: outer bottom, home row
     *   3: bottom row                 4: thumbs fn sec pri rch | rch pri sec fn
     */
    [DEF] = LAYOUT(
        KC_NUBS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
        KC_BSLS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC,
                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        LSFT_T(KC_GRV), LT(NUM, KC_BSPC), LSFT_T(KC_TAB), LGUI_T(KC_ESC),
                                                        LT(SYM, KC_ENT), LT(NAV, KC_SPC), HYP, KC_RALT
    ),

    [SYM] = LAYOUT(
        KC_LCTL, KC_AT,   KC_PLUS, KC_LBRC, KC_RBRC, KC_CIRC,      KC_DLR,  KC_NO,      KC_NO,   KC_NO,       KC_NO,   KC_RCTL,
        KC_LALT, KC_MINS, KC_EQL,  KC_LPRN, KC_RPRN, KC_ASTR,      KC_PERC, KC_EXLM,    KC_NO,   KC_NO,       KC_RALT, KC_RBRC,
                 KC_AMPR, KC_HASH, KC_LCBR, KC_RCBR, KC_UNDS,      KC_NUHS, G(KC_MINS), G(KC_0), G(KC_EQL),   KC_NO,
        KC_LGUI, KC_TRNS, KC_LSFT, KC_ESC,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_RGUI
    ),

    [NAV] = LAYOUT(
        HY(KC_3), GLOBE,   KC_PGUP, G(C(KC_V)), G(KC_LEFT),  HY(KC_BSLS),   HY(KC_BSLS),        KC_F1,            KC_F2,           G(S(KC_A)),        HY(KC_QUOT),       HY(KC_2),
        HY(KC_4), KC_INS,  KC_LEFT, KC_UP,      KC_RGHT,     G(KC_SPC),     OSM(MOD_LSFT | MOD_LGUI), SMOD(MOD_RGUI), SMOD(MOD_LALT), SMOD(MOD_RSFT), SMOD(MOD_RCTL), HY(KC_1),
                  KC_DEL,  KC_PGDN, KC_DOWN,    G(KC_RGHT),  KC_ESC,        KC_NO,              SGUI(KC_LBRC),    SMOD(MOD_LALT),  SGUI(KC_RBRC),     G(KC_SPC),
        KC_NO,    KC_BSPC, KC_TAB,  KC_ENT,                                 KC_TRNS,            KC_TRNS,          KC_TRNS,         KC_NO
    ),

    [NUM] = LAYOUT(
        KC_NO,   KC_NO,          C(S(KC_TAB)),   G(C(KC_V)),     C(KC_TAB),      KC_NO,      KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PMNS, KC_NO,
        KC_NO,   SMOD(MOD_LCTL), SMOD(MOD_LSFT), SMOD(MOD_LALT), SMOD(MOD_LGUI), KC_HOME,    KC_PAST, KC_4,    KC_5,    KC_6,    KC_PPLS, KC_NO,
                 G(KC_SPC),      APP_PREV,       WIN_NEXT,       APP_NEXT,       KC_END,     KC_PDOT, KC_1,    KC_2,    KC_3,    KC_DOT,
        KC_NO,   KC_BSPC,        KC_TRNS,        KC_TRNS,                                    KC_PENT, KC_0,    KC_COMM, KC_NO
    ),

    [FN] = LAYOUT(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,        KC_NO,   KC_PAUS,        KC_SCRL,        KC_NUM,         KC_CAPS,        KC_NO,
        KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,        GLOBE,   SMOD(MOD_RGUI), SMOD(MOD_LALT), SMOD(MOD_RSFT), SMOD(MOD_RCTL), KC_NO,
                 KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,        KC_NO,   KC_PAUS,        SMOD(MOD_LALT), KC_NUM,         KC_CAPS,
        KC_NO,   KC_BSPC, KC_TAB,  KC_ESC,                         KC_TRNS, KC_TRNS,        KC_TRNS,        KC_NO
    ),

    // ZMK-only keys (Bluetooth, battery/connection indicators, Studio unlock) are KC_NO
    [ADJ] = LAYOUT(
        KC_NO,   KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_VOLU,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT
    ),
};
// clang-format on

static bool is_smod(uint16_t keycode) {
    return IS_QK_MOD_TAP(keycode) && QK_MOD_TAP_GET_TAP_KEYCODE(keycode) == KC_F23;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return !is_smod(keycode);
}

// ZMK quick-tap is set only for &mt and &lt
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    if (keycode == HYP || is_smod(keycode)) {
        return 0;
    }
    return QUICK_TAP_TERM;
}

// 5-bit mod-tap mods -> 8-bit HID mod bits
static uint8_t mod5_to_mod8(uint8_t mod5) {
    return (mod5 & 0x10) ? (mod5 & 0x0F) << 4 : (mod5 & 0x0F);
}

// App/window switcher (ZMK tri-state): the first press holds Cmd or Opt,
// next presses only tap Tab, any other key or a layer change releases it.
static uint8_t switcher_mod = 0;

static void switcher_end(void) {
    if (switcher_mod) {
        unregister_mods(switcher_mod);
        switcher_mod = 0;
    }
}

static void switcher_tap(uint8_t mod, uint16_t tab) {
    if (switcher_mod != mod) {
        switcher_end();
        switcher_mod = mod;
        register_mods(mod);
    }
    tap_code16(tab);
}

// ZMK conditional layers
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, SYM, NAV, ADJ);
    state = update_tri_layer_state(state, NUM, SYM, FN);
    if (state != layer_state) {
        switcher_end();
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;

    switch (keycode) {
        case APP_NEXT:
            if (pressed) switcher_tap(MOD_BIT(KC_LGUI), KC_TAB);
            return false;
        case APP_PREV:
            if (pressed) switcher_tap(MOD_BIT(KC_LGUI), S(KC_TAB));
            return false;
        case WIN_NEXT:
            if (pressed) switcher_tap(MOD_BIT(KC_LALT), KC_TAB);
            return false;
    }

    if (pressed) {
        switcher_end();
    }

    switch (keycode) {
        case GLOBE:
            host_consumer_send(pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false;
        case HYP:
            if (record->tap.count) {
                if (pressed) add_oneshot_mods(MOD_BIT(KC_LCTL));
                return false;
            }
            break;
        default:
            if (is_smod(keycode) && record->tap.count) {
                if (pressed) add_oneshot_mods(mod5_to_mod8(QK_MOD_TAP_GET_MODS(keycode)));
                return false;
            }
    }
    return true;
}

// Status LED (on-board WS2812). Highest priority first:
//   bootloader: white; app switcher: blinks green; sticky mod pending:
//   blinks the layer color (white on DEFAULT); layer: steady color;
//   DEFAULT: off. Goes dark together with the OLED when idle.
#define STATUS_LED_BRIGHTNESS 48 // of 255: the WS2812 is very bright
#define STATUS_LED_BLINK_MS 250
#define STATUS_LED_TIMEOUT OLED_TIMEOUT

typedef struct {
    uint8_t r, g, b;
} color_t;

static const color_t BLACK = {0, 0, 0};
static const color_t WHITE = {255, 255, 255};

static const color_t layer_colors[] = {
    [DEF] = {0, 0, 0},       // off
    [SYM] = {255, 180, 0},   // yellow
    [NAV] = {0, 60, 255},    // blue
    [NUM] = {0, 255, 40},    // green
    [FN]  = {170, 0, 255},   // purple
    [ADJ] = {255, 0, 0},     // red
};

static color_t status_led_shown = {1, 1, 1}; // forces the first update

static void status_led_set(color_t c) {
    if (c.r == status_led_shown.r && c.g == status_led_shown.g && c.b == status_led_shown.b) {
        return;
    }
    status_led_shown = c;
    ws2812_set_color_all(c.r * STATUS_LED_BRIGHTNESS / 255, c.g * STATUS_LED_BRIGHTNESS / 255, c.b * STATUS_LED_BRIGHTNESS / 255);
    ws2812_flush();
}

static color_t status_led_color(void) {
    bool    blink_on = (timer_read() / STATUS_LED_BLINK_MS) % 2 == 0;
    uint8_t layer    = get_highest_layer(layer_state);

    if (switcher_mod) {
        return blink_on ? layer_colors[NUM] : BLACK;
    }
    if (get_oneshot_mods()) {
        return blink_on ? (layer == DEF ? WHITE : layer_colors[layer]) : BLACK;
    }
    if (last_input_activity_elapsed() > STATUS_LED_TIMEOUT) {
        return BLACK;
    }
    return layer_colors[layer];
}

void keyboard_post_init_user(void) {
    ws2812_init();
    status_led_set(BLACK);
}

void housekeeping_task_user(void) {
    status_led_set(status_led_color());
}

// Runs right before QK_BOOT jumps to the bootloader
bool shutdown_user(bool jump_to_bootloader) {
    status_led_set(jump_to_bootloader ? WHITE : BLACK);
    return true;
}

#ifdef OLED_ENABLE
static const char *layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case SYM: return "SYMBOLS";
        case NAV: return "NAV";
        case NUM: return "NUMBERS";
        case FN:  return "FN KEYS";
        case ADJ: return "ADJUST";
        default:  return "DEFAULT";
    }
}

bool oled_task_user(void) {
    oled_write_ln_P(PSTR("Kryla rev1"), false);
    oled_write_ln_P(PSTR(""), false);

    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln(layer_name(), false);

    uint8_t mods = get_mods() | get_oneshot_mods() | switcher_mod;
    oled_write_P(PSTR("Mods:  "), false);
    oled_write_P(PSTR("CTL"), mods & MOD_MASK_CTRL);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("SFT"), mods & MOD_MASK_SHIFT);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("OPT"), mods & MOD_MASK_ALT);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("CMD"), mods & MOD_MASK_GUI);

    led_t leds = host_keyboard_led_state();
    oled_write_P(PSTR("Locks: "), false);
    oled_write_P(PSTR("CAPS"), leds.caps_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("NUM"), leds.num_lock);
    return false;
}
#endif
