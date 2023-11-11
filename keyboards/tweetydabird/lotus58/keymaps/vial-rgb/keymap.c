// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define ____ KC_TRNS

#ifdef AUTO_SHIFT_ENABLE

void keyboard_post_init_user(void) {
	autoshift_disable();
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
    QK_GESC, 	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_MPLY,	KC_MPLY,	KC_6,	KC_7,	KC_8,		KC_9,		KC_0,		KC_MINS,
    KC_TAB, 	KC_Q,	KC_W,   KC_E,   KC_R,   KC_T,                       	KC_Y, 	KC_U,   KC_I,   	KC_O,   	KC_P,   	KC_LBRC,
	KC_NUHS, 	KC_A, 	KC_S,   KC_D,   KC_F,   KC_G,                      	 	KC_H, 	KC_J,   KC_K,   	KC_L,	   	KC_SCLN,	KC_QUOT,
	LCTL_T(KC_LEFT), 	KC_Z, 	KC_X,   KC_C,   KC_V,   KC_B, 	KC_DOWN,		KC_UP,  KC_N, 	KC_M,   KC_COMM,	KC_DOT, 	KC_SLSH, 	RCTL_T(KC_RIGHT),
						KC_DEL, TG(1), 		LALT_T(KC_LGUI),	LSFT_T(KC_SPACE),    	RSFT_T(KC_ENTER), 	RALT_T(KC_APP), 		TG(2), 			KC_BSPC
	),
 
    [1] = LAYOUT(
    ____, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, ____,        ____, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
	____, ____, ____, ____, ____, ____,                    ____, ____, ____, ____, ____, ____,
	____, ____, ____, ____, ____, ____,                    ____, ____, ____, ____, ____, ____,
	____, ____, ____, ____, ____, ____, KC_PGDN,        KC_PGUP, ____, ____, ____, ____, ____, ____,
					  ____, ____, ____, ____,      	 ____, ____, ____, ____
    ),

    [2] = LAYOUT(
    ____, ____, ____, ____, ____, ____, ____,        ____, ____, ____, ____, ____, ____, ____,
	____, ____, ____, ____, ____, ____,                    ____, ____, ____, ____, ____, ____,
	____, ____, ____, ____, ____, ____,                    ____, ____, ____, ____, ____, ____,
	____, ____, ____, ____, ____, ____, ____,        ____, ____, ____, ____, ____, ____, ____,
					  ____, ____, ____, ____,      	 ____, ____, ____, ____
    ),

    [3] = LAYOUT(
    QK_BOOT, ____, ____, ____, NK_TOGG, AC_TOGG, ____,        ____, ____, ____, ____, RGB_VAI, RGB_VAD, RGB_TOG,
	QK_RBT, ____, ____, ____, ____, ____,                    ____, ____, ____, RGB_HUI, RGB_HUD, RGB_M_P,
	____, ____, ____, ____, ____, ____,                    ____, ____, ____, RGB_SAI, RGB_SAD, RGB_M_B,
	____, ____, ____, ____, ____, ____, ____,        ____, ____, ____, ____, RGB_SPI, RGB_SPD, RGB_M_R,
					  ____, ____, ____, ____,      	 ____, ____, ____, ____
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

#ifdef OLED_ENABLE

static void print_status_narrow(void) {
	// Create OLED content
    oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
	oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case 3:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
	
	// Display capslock
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);

    // Display numlock
    oled_write_P(PSTR("\n"), false);
    oled_write_ln_P(PSTR("Num-  lock"), led_usb_state.num_lock);
	
#ifdef AUTO_SHIFT_ENABLE

	bool autoshift = get_autoshift_state();
	oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR("Auto-Shift"), autoshift);
	oled_write_P(PSTR("\n"), false);
	
#endif

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_270;
    } else {
		return OLED_ROTATION_270;
	}
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_status_narrow();
    }
	return false;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, 1, 2, 3);
}

// RGB matrix
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { 
    {   
    // Key Matrix to LED Index
    // Left Half
    {  5,  4,  3,  2,  1,  0 },
    {  6,  7,  8,  9, 10, 11 },
    { 17, 16, 15, 14, 13, 12 },
    { 18, 19, 20, 21, 22, 23 },
    { NO_LED, 28, 27, 26, 25, 24 },
    // Right Half
    { 34, 33, 32, 31, 30, 29 },
    { 35, 36, 37, 38, 39, 40 },
    { 46, 45, 44, 43, 42, 41 },
    { 47, 48, 49, 50, 51, 52 },
    { NO_LED, 57, 56, 55, 54, 53 }
    },
    {
    // LED Index to Physical Position
    // Left Half
    { 80, 4  }, { 64, 2  }, { 48, 0  }, { 32, 2  }, { 16, 5  }, {  0, 7  },
    {  0, 23 }, { 16, 21 }, { 32, 18 }, { 48, 16 }, { 64, 18 }, { 80, 20 }, 
    { 80, 36 }, { 64, 34 }, { 48, 32 }, { 32, 34 }, { 16, 37 }, {  0, 38 },
    {  0, 55 }, { 16, 53 }, { 32, 50 }, { 48, 48 }, { 64, 50 }, { 80, 52 },
                                                                        { 100, 44 }, 
                                { 92, 61 },  { 72, 64 }, { 56, 62 }, { 40, 60 },

    // Right Half
            { 144, 4  }, { 160, 2  }, { 176, 0  }, { 192, 2  }, { 208, 5  }, { 224, 7  },
            { 224, 23 }, { 208, 21 }, { 192, 18 }, { 176, 16 }, { 160, 18 }, { 144, 20 },
            { 144, 36 }, { 160, 34 }, { 176, 32 }, { 192, 34 }, { 208, 37 }, { 224, 38 },
            { 224, 55 }, { 208, 53 }, { 192, 50 }, { 176, 48 }, { 160, 50 }, { 144, 52 },
    { 124, 44 }, 
        { 132, 61 }, { 152, 64 }, { 168, 62 }, { 184, 60 },

    },
    {
    // LED Index to Flag
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,   4, 
            4, 4, 4, 4,

        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
    4,  4, 4, 4, 4, 4, 4, 
       4, 4, 4, 4

    }
};
#endif