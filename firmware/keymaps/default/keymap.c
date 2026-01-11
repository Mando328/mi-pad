// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layers {
    _BASE,   // Base layer
    _FN      // Function layer (secondary layer)
};
// Define custom keycodes for music layer macros
enum custom_keycodes {
    MUS_PLAY = SAFE_RANGE,
    MUS_REC,
    MUS_UNDO,
    MUS_CUT,
    MUS_COPY,
    MUS_PASTE,
    MUS_LEFT,
    MUS_RIGHT,
    MUS_SNAP,
    OPEN_MESSENGER
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true; // only act on press

    switch(keycode) {
        case MUS_PLAY:   SEND_STRING(SS_LCTL("space")); break;      // Play/Stop
        case MUS_REC:    SEND_STRING(SS_LCTL("r")); break;          // Record
        case MUS_UNDO:   SEND_STRING(SS_LCTL("z")); break;          // Undo
        case MUS_CUT:    SEND_STRING(SS_LCTL("x")); break;          // Cut
        case MUS_COPY:   SEND_STRING(SS_LCTL("c")); break;          // Copy
        case MUS_PASTE:  SEND_STRING(SS_LCTL("v")); break;          // Paste
        case MUS_LEFT:   SEND_STRING(SS_LCTL("left")); break;       // Move Left
        case MUS_RIGHT:  SEND_STRING(SS_LCTL("right")); break;      // Move Right  
        case OPEN_MESSENGER: SEND_STRING("https://www.messenger.com\n"); return true;
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┬────┬────┐
     * │  A │ wb │  C │
     * ├────┼────┼────┤
     * │  D │  E │  F │
     * ├────┼────┼────┤
     * │  G │  H │ Fn │
     * └────┴────┴────┘
     */
    [_BASE] = LAYOUT(
        KC_A,    KC_WWW_HOME,    OPEN_MESSENGER,
        KC_D,    KC_E,    KC_F,
        KC_G,    KC_H,    TG(_FN)
    ),
    [_FN] = LAYOUT(
           MUS_PLAY,    MUS_REC,    MUS_UNDO,
        MUS_CUT,     MUS_COPY,   MUS_PASTE,
        MUS_LEFT,    MUS_RIGHT,  TG(_BASE)     // Bottom row: Volume Up, Volume Down, Back to Base layer
    )
};


const uint16_t PROGMEM encoder_map[][1][2] = {
    [0] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
};

extern bool encoder_pressed[];

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_KB_VOLUME_UP);
    } else {
        tap_code(KC_KB_VOLUME_DOWN);
    }
    if (encoder_pressed[index]) {
        tap_code(KC_AUDIO_MUTE);
    }
    return true;
}