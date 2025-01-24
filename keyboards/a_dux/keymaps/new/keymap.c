#include QMK_KEYBOARD_H
// #include "keymap_german.h"

#define _COLEMAKDH 0
#define _LOWER 2
#define _RAISE 3
#define _EXTRA 4
#define _MOUSE 6


enum {
	TAB_LOWER,
	ENTER_RAISE,
	BSPC_EXTRA,
	SPC_MOUSE,
	Q_ESC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAKDH] = LAYOUT( \
  KC_Q,  KC_W,  KC_F,  KC_P,  KC_B,  KC_J,  KC_L,  KC_U,  KC_Y, KC_SEMICOLON,  \
  LGUI_T(KC_A),  LALT_T(KC_R),  LCTL_T(KC_S),  LSFT_T(KC_T),  KC_G, KC_M,  RSFT_T(KC_N),  RCTL_T(KC_E),  LALT_T(KC_I),  RGUI_T(KC_O),  \
  KC_Z,  KC_X,  KC_C,  KC_D,  KC_V,  KC_K,  KC_H,  KC_COMMA,  RALT_T(KC_DOT), KC_SLASH,  \
  TD(BSPC_EXTRA), TD(TAB_LOWER),  	TD(ENTER_RAISE),  	 KC_SPC \
),

[_LOWER] = LAYOUT( \
  KC_1, 	 KC_2, 	  KC_3,   	KC_4, 		KC_5,  	 KC_6, 	  KC_7,       KC_8,    KC_9, 	KC_0, 	\
  KC_LEFT,    KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_HOME, 	KC_PGDN, KC_PGUP, KC_END, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  TO(_COLEMAKDH),	XXXXXXX, XXXXXXX, KC_SPC \
),

[_RAISE] = LAYOUT(
  KC_EXLM, KC_AT, KC_HASH,   	KC_DLR, 	KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_PIPE, 	 KC_BSLS, XXXXXXX, 	KC_QUOT,  KC_DQUO, KC_PLUS, KC_MINS, S(KC_UNDS), S(KC_LCBR), KC_RCBR,  \
  KC_TILD, KC_GRV, 	KC_GRV, 	XXXXXXX, XXXXXXX, KC_EQL, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, \
  TO(_COLEMAKDH), KC_DEL,  XXXXXXX,   XXXXXXX   \
),

[_EXTRA] = LAYOUT(
		  KC_ESC, XXXXXXX, XXXXXXX,   	XXXXXXX, 	XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, QK_BOOT, \
  XXXXXXX, 	 XXXXXXX, XXXXXXX, 	XXXXXXX, 	XXXXXXX, KC_H, KC_J, KC_K, KC_L, XXXXXXX, \
  TO(_COLEMAKDH), XXXXXXX, XXXXXXX, 	XXXXXXX, 	XXXXXXX, KC_BSPC, KC_DEL , XXXXXXX, XXXXXXX ,  KC_CAPS, \
  XXXXXXX,  XXXXXXX, KC_ESC,  TO(_MOUSE) \
),


    [_MOUSE] = LAYOUT(
  TO(_COLEMAKDH),  KC_MS_WH_LEFT, KC_MS_WH_DOWN,  KC_MS_WH_UP, XXXXXXX, XXXXXXX, KC_MS_BTN1, KC_MS_BTN2, XXXXXXX, XXXXXXX , \
  KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN1, XXXXXXX, 	KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP,  KC_MS_RIGHT, KC_MS_WH_RIGHT, \
  KC_MS_WH_LEFT, KC_MS_ACCEL1, KC_MS_ACCEL2, TO(_COLEMAKDH), 	XXXXXXX,   XXXXXXX, KC_LCTL,    XXXXXXX, XXXXXXX,KC_MS_WH_RIGHT,    \
  TO(_COLEMAKDH), KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_LEFT \
),

};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;


enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
};

/*enum {*/
    /*QUOT_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum */
/*};*/

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
uint8_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void tl_finished(tap_dance_state_t *state, void *user_data);
void tl_reset(tap_dance_state_t *state, void *user_data);
void er_finished(tap_dance_state_t *state, void *user_data);
void er_reset(tap_dance_state_t *state, void *user_data);
void be_finished(tap_dance_state_t *state, void *user_data);
void be_reset(tap_dance_state_t *state, void *user_data);
void sm_finished(tap_dance_state_t *state, void *user_data);
void sm_reset(tap_dance_state_t *state, void *user_data);
void qe_finished(tap_dance_state_t *state, void *user_data);
void qe_reset(tap_dance_state_t *state, void *user_data);

// Determine the current tap dance state
uint8_t cur_dance(tap_dance_state_t *state) {
    /*if (state->count == 1) {*/
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    /*} //else if (state->count == 2) return SINGLE_TAP;*/
    /*else return 8;*/
}

// Initialize tap structure associated with example tap dance key
static tap tl_tap_state = {
    .is_press_action = true,
    .state = 0
};
static tap er_tap_state = {
    .is_press_action = true,
    .state = 0
};
static tap be_tap_state = {
    .is_press_action = true,
    .state = 0
};

static tap sm_tap_state = {
    .is_press_action = true,
    .state = 0
};

static tap qe_tap_state = {
    .is_press_action = true,
    .state = 0
};


// Functions that control what our tap dance key does
void er_finished(tap_dance_state_t *state, void *user_data) {
    er_tap_state.state = cur_dance(state);
    switch (er_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case SINGLE_HOLD:
            layer_on(_RAISE);
            break;
    }
}

void er_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (er_tap_state.state == SINGLE_HOLD) {
        layer_off(_RAISE);
    }
    er_tap_state.state = 0;
}


// Functions that control what our tap dance key does
void tl_finished(tap_dance_state_t *state, void *user_data) {
    tl_tap_state.state = cur_dance(state);
    switch (tl_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case SINGLE_HOLD:
            layer_on(_LOWER);
            break;
    }
}

void tl_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (tl_tap_state.state == SINGLE_HOLD) {
        layer_off(_LOWER);
    }
    tl_tap_state.state = 0;
}


// Functions that control what our tap dance key does
void be_finished(tap_dance_state_t *state, void *user_data) {
    be_tap_state.state = cur_dance(state);
    switch (be_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_BSPC);
            break;
        case SINGLE_HOLD:
            layer_on(_EXTRA);
            break;
    }
}

void be_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (be_tap_state.state == SINGLE_HOLD) {
        layer_off(_EXTRA);
    }
    be_tap_state.state = 0;
}

// Functions that control what our tap dance key does
void sm_finished(tap_dance_state_t *state, void *user_data) {
    sm_tap_state.state = cur_dance(state);
    switch (sm_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case SINGLE_HOLD:
	    layer_on(_MOUSE);
            break;
    }
}

void sm_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (sm_tap_state.state == SINGLE_HOLD) {
        /*layer_off(_EXTRA);*/
    }
    sm_tap_state.state = 0;
}




// Functions that control what our tap dance key does
void qe_finished(tap_dance_state_t *state, void *user_data) {
    qe_tap_state.state = cur_dance(state);
    switch (qe_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_Q);
            break;
        case SINGLE_HOLD:
            tap_code(KC_ESC);
            /*layer_on(KC_ESC);*/
            break;
    }
}

void qe_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (qe_tap_state.state == SINGLE_HOLD) {
        /*layer_off(_EXTRA);*/
    }
    qe_tap_state.state = 0;
}



// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
	[ENTER_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, er_finished, er_reset),
	[TAB_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tl_finished, tl_reset),
	[BSPC_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, be_finished, be_reset),
	[SPC_MOUSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sm_finished, sm_reset),
	[Q_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qe_finished, qe_reset)
};

/// Define per key tapping terms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_N):
            return 150;
        case LSFT_T(KC_T):
            return 150;
        default:
            return TAPPING_TERM;
    }
}




