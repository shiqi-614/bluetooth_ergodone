#include "ErgodoneKeymap.h"
#include "config.h"
#include <KeyboardFirmware.h>

BluetoothHost host;
Mcp23017PlusBluetoothBleMatrix matrix;
KeyboardFirmware_ KeyboardFirmware;

bool CAPS_LED = false;
bool BTN1 = false;

void setup()
{

    pinMode(LEDA_PIN, OUTPUT);
    pinMode(LEDB_PIN, OUTPUT);
    pinMode(LEDC_PIN, OUTPUT);

    if (debug_enable) {
        Serial.begin(9600);
        while (!Serial)
            ;
    }
    print_set_sendchar(arduino_tmk_sendchar);
    dprintf("debug enable %d\n", debug_enable);
    KeyboardFirmware.begin(host, matrix);
}

void loop()
{
    KeyboardFirmware.runTask();
}

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
    dprint("== action function called");
    dprintln();
    dprint("=  id:      ");
    dprintf("%u", id);
    dprintln();
    dprint("=  pressed: ");
    dprintf("%u", record->event.pressed);
    dprint("=  opt: ");
    dprintf("%u", opt);
    dprintln();

    // Position to add your custom functions.
    // Such as you can write function to connect different devices
    // when press some specific buttons,
    // if you can custom program in bluetooth HID chip.
    // Foe example, adding following line in fn_actions.
    //   [0] =  ACTION_FUNCTION(such as id of first device),
    //   [1] =  ACTION_FUNCTION(such as id of second device),
    //   ...
    // then press FN0 to eonnect your computer,
    // press FN1 to connect your ipad
    // ...
    dprintf("== end of action function\n");
}

extern "C" {

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    ERGODONE_KEYMAP(
        GRV, 1, 2, 3, 4, 5, FN16,
        TAB, Q, W, E, R, T, LBRC,
        FN4, A, S, D, F, G,
        LSFT, FN3, Z, X, C, V, EQL,
        LCTL, LALT, LEFT, RGHT, LGUI,
        F12, FN0,
        FN1,
        SPC, ESC, FN2,

        6, 7, 8, 9, 0, MINS, EQL,
        RBRC, Y, U, I, O, P, BSLS,
        H, J, K, L, SCLN, QUOT,
        B, N, M, COMM, DOT, SLSH, RSFT,
        NO, DOWN, UP, CAPS, RCTL,
        MUTE, MPLY,
        VOLU,
        VOLD, BSPC, ENT),
    ERGODONE_KEYMAP(
        TRNS, F1, F2, F3, F4, F5, F6,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, FN10, FN9, FN11,
        LSFT, FN3, LSFT, TRNS, TRNS, TRNS, FN6,
        TRNS, TRNS, LALT, TRNS, TRNS,
        TRNS, FN0,
        FN1,
        SPC, FN4, FN2,

        F6, F7, F8, F9, F10, F11, F12,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RBRC,
        LEFT, DOWN, UP, RGHT, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS,
        TRNS,
        TRNS, TRNS, TRNS),

    ERGODONE_KEYMAP(
        TRNS, F1, F2, F3, F4, F5, F6,
        TAB, FN7, FN8, FN12, FN12, NO, TRNS,
        TRNS, ACL2, ACL1, ACL0, FN8, NO,
        LSFT, NO, NO, NO, FN7, NO, FN6,
        LCTL, LALT, MPLY, MPRV, BTN1,
        TRNS, FN0,
        FN1,
        FN5, FN4, FN2,

        F6, F7, F8, FN13, FN14, FN15, F12,
        VOLU, BTN1, BTN2, TRNS, TRNS, TRNS, RBRC,
        LEFT, DOWN, UP, RGHT, TRNS, TRNS,
        VOLD, WH_R, WH_U, WH_D, WH_L, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS,
        TRNS,
        TRNS, BTN2, BTN1),

};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
    dprintf("macro begin id %u opt %u.\n", id, opt);

    switch (id) {
    case 0:
        return (record->event.pressed ? MACRO(I(0), D(LSHIFT), T(H), U(LSHIFT), T(E), T(L), T(L), T(O), T(SPC), D(LSHIFT), T(W), U(LSHIFT), T(O), T(R), T(L), T(D), END) : MACRO_NONE);
    case 1: // alfred
        return (record->event.pressed ? MACRO(D(LGUI), D(SPC), U(LGUI), U(SPC), END) : MACRO_NONE);
    case 2: // clipboard
        return (record->event.pressed ? MACRO(D(LGUI), D(LALT), T(C), U(LGUI), U(LALT), END) : MACRO_NONE);
    case 3: // vimac
        return (record->event.pressed ? MACRO(D(LSHIFT), D(LCTL), T(F), U(LSHIFT), U(LCTL), END) : MACRO_NONE);
    case 4: // full screen
        return (record->event.pressed ? MACRO(D(LALT), D(LGUI), T(F), U(LALT), U(LGUI), END) : MACRO_NONE);
    case 5: // left half screen
        return (record->event.pressed ? MACRO(D(LALT), D(LGUI), T(LEFT), U(LALT), U(LGUI), END) : MACRO_NONE);
    case 6: // right half screen
        return (record->event.pressed ? MACRO(D(LALT), D(LGUI), T(RGHT), U(LALT), U(LGUI), END) : MACRO_NONE);
    case 7: // vimac scroll
        return (record->event.pressed ? MACRO(D(LALT), D(LGUI), T(E), U(LALT), U(LGUI), END) : MACRO_NONE);
    case 8: // (
        return (record->event.pressed ? MACRO(D(LSHIFT), D(9), T(9), U(LSHIFT), END) : MACRO_NONE);
    case 9: // )
        return (record->event.pressed ? MACRO(D(LSHIFT), D(0), T(0), U(LSHIFT), END) : MACRO_NONE);
    case 10: // _
        return (record->event.pressed ? MACRO(D(LSHIFT), D(MINS), T(MINS), U(LSHIFT), END) : MACRO_NONE);
    case 11: // alt + space to trigger accessMenuBarApps and Hidden Bar
        return (record->event.pressed ? MACRO(D(LALT), D(SPC), T(SPC), U(LALT), END) : MACRO_NONE);
    }
    return MACRO_NONE;
}

static const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_SET((uint16_t)0, ON_PRESS),
    [1] = ACTION_LAYER_SET((uint16_t)1, ON_PRESS),
    [2] = ACTION_LAYER_SET((uint16_t)2, ON_PRESS),
    [3] = ACTION_LAYER_MOMENTARY((uint16_t)1),
    [4] = ACTION_LAYER_MOMENTARY((uint16_t)2),
    [5] = ACTION_MACRO((uint16_t)1),
    [6] = ACTION_MACRO((uint16_t)0),
    [7] = ACTION_MACRO((uint16_t)2),
    [8] = ACTION_MACRO((uint16_t)3),
    [9] = ACTION_MACRO((uint16_t)4),
    [10] = ACTION_MACRO((uint16_t)5),
    [11] = ACTION_MACRO((uint16_t)6),
    [12] = ACTION_MACRO((uint16_t)7),
    [13] = ACTION_MACRO((uint16_t)8),
    [14] = ACTION_MACRO((uint16_t)9),
    [15] = ACTION_MACRO((uint16_t)10),
    [16] = ACTION_MACRO((uint16_t)11),
};

uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    return action;
}

void hook_matrix_change(keyevent_t event)
{
    action_t action = layer_switch_get_action(event);
    switch (action.key.code) {
    case KC_CAPSLOCK: {
        if (event.pressed) {
            if (CAPS_LED) {
                dprintf("turn off led of CAPSLOCK\n");
                digitalWrite(LEDA_PIN, LOW);
                CAPS_LED = false;
            } else {
                dprintf("turn on led of CAPSLOCK\n");
                digitalWrite(LEDA_PIN, HIGH);
                CAPS_LED = true;
            }
            break;
        }
        break;
    }
    case KC_MS_BTN1: {
        if (event.pressed) {
            BTN1 = true;
        } else {
            BTN1 = false;
        }
        break;
    }
    }
}

void hook_layer_change(uint32_t layer_state)
{
    dprintf("hook layer change layer_state -> %d\n", layer_state);

    digitalWrite(LEDB_PIN, LOW);
    digitalWrite(LEDC_PIN, LOW);

    if (layer_state & (1 << 1)) {
        digitalWrite(LEDC_PIN, HIGH);
    }
    if (layer_state & (1 << 2)) {
        digitalWrite(LEDB_PIN, HIGH);
    }
    if (layer_state & (1 << 3)) {
        digitalWrite(LEDB_PIN, HIGH);
        digitalWrite(LEDC_PIN, HIGH);
    }
}
}
