/* sokol_input.h -- https://github.com/takeiteasy/sokol_helpers
 
 Very basic input manager that keeps track of keys state, mouse position, mouse-
 delta position, mouse buttons state and mouse wheel state. (for now)
 
 The MIT License (MIT)
 
 Copyright (c) 2024 George Watson
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge,
 publish, distribute, sublicense, and/or sell copies of the Software,
 and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef SOKOL_HELPER_INPUT
#define SOKOL_HELPER_INPUT
#if defined(__cplusplus)
extern "C" {
#endif

#ifndef SOKOL_APP_INCLUDED
#error "Please include sokol_app.h before the sokol_input.h implementation"
#endif
#ifndef SOKOL_TIME_INCLUDED
#error "Please include sokol_time.h before the sokol_input.h implementation"
#endif
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

// Clear the input state
void sokol_input_clear(void);
// Assign sapp_desc.event_cb = sokol_input_handler
// Or just pass the event to it inside the callback
void sokol_input_handler(const sapp_event *event);
// Call this at the end of sapp frame callback
void sokol_input_update(void);

int sapp_is_key_down(int key);
// This will be true if a key is held for more than 1 second
// TODO: Make the duration configurable
int sapp_is_key_held(int key);
// Returns true if key is down this frame and was up last frame
int sapp_was_key_pressed(int key);
// Returns true if key is up and key was down last frame
int sapp_was_key_released(int key);
// If any of the keys passed are not down returns false
int sapp_are_keys_down(int n, ...);
// If none of the keys passed are down returns false
int sapp_any_keys_down(int n, ...);
int sapp_is_button_down(int button);
int sapp_is_button_held(int button);
int sapp_was_button_pressed(int button);
int sapp_was_button_released(int button);
int sapp_are_buttons_down(int n, ...);
int sapp_any_buttons_down(int n, ...);
int sapp_has_mouse_move(void);
// Checks if only passed modifier flags are on, if another modifier is flagged
// but not passed to the function, it will return false. For example, if the
// user is holding down, CTRL and SHIFT, check_only(CTRL, SHIFT) returns true.
// However, if the user is holding down CTRL, SHIFT and ALT,
// check_only(CTRL, SHIFT) would return false. This obviously also includes
// situations like CTRL, SHIFT is down check(CTRL) would return false.
int sapp_modifier_check_only(int n, ...);
// Checks if each modifier passed is down, if any are false returns false
int sapp_modifier_check_each(int n, ...);
// Checks if any of the modifiers are true, if none are true return false
int sapp_modifier_check_any(int n, ...);
// Check if modifier is down, doesn't check if other
int sapp_modifier_check_in(int modifier);
// Checks if there are any modifiers at all
int sapp_any_modifiers(void);
int sapp_cursor_x(void);
int sapp_cursor_y(void);
int sapp_cursor_delta_x(void);
int sapp_cursor_delta_y(void);
int sapp_check_scrolled(void);
float sapp_scroll_x(void);
float sapp_scroll_y(void);

// Taken from: https://gist.github.com/61131/7a22ac46062ee292c2c8bd6d883d28de
#ifndef N_ARGS
#define N_ARGS(...) _NARG_(__VA_ARGS__, _RSEQ())
#define _NARG_(...) _SEQ(__VA_ARGS__)
#define _SEQ(_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108,_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122,_123,_124,_125,_126,_127,N,...) N
#define _RSEQ() 127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#endif

#define SAPP_ARE_KEYS_DOWN(...) sapp_are_keys_down(N_ARGS(__VA_ARGS__), __VA_ARGS__)
#define SAPP_ANY_KEYS_DOWN(...) sapp_any_keys_down(N_ARGS(__VA_ARGS__), __VA_ARGS__)
#define SAPP_ARE_BUTTONS_DOWN(...) sapp_are_buttons_down(N_ARGS(__VA_ARGS__), __VA_ARGS__)
#define SAPP_ANY_BUTTONS_DOWN(...) sapp_any_buttons_down(N_ARGS(__VA_ARGS__), __VA_ARGS__)
#define SAPP_MODIFIER_CHECK_ONLY(...) sapp_modifier_check_only(N_ARGS(__VA_ARGS__), __VA_ARGS__)
#define SAPP_MODIFIER_CHECK_EACH(...) sapp_modifier_check_each(N_ARGS(__VA_ARGS__), __VA_ARGS__)
#define SAPP_MODIFIER_CHECK_ANY(...) sapp_modifier_check_any(N_ARGS(__VA_ARGS__), __VA_ARGS__)

#if defined(__cplusplus)
}
#endif
#endif // SOKOL_HELPER_INPUT

#ifdef SOKOL_HELPER_IMPL
typedef struct {
    int down;
    uint64_t timestamp;
} input_state_t;

typedef struct {
    input_state_t keys[SAPP_KEYCODE_MENU+1];
    input_state_t buttons[3];
    int modifier;
    struct {
        int x, y;
    } cursor;
    struct {
        float x, y;
    } scroll;
} input_t;

#ifndef DEFAULT_KEY_HOLD_DELAY
#define DEFAULT_KEY_HOLD_DELAY 1
#endif

static input_t prev, current;

void sokol_input_clear(void) {
    memset(&prev,    0, sizeof(input_t));
    memset(&current, 0, sizeof(input_t));
}

void sokol_input_handler(const sapp_event* e) {
    switch (e->type) {
        case SAPP_EVENTTYPE_KEY_UP:
        case SAPP_EVENTTYPE_KEY_DOWN:
            current.keys[e->key_code].down = e->type == SAPP_EVENTTYPE_KEY_DOWN;
            current.keys[e->key_code].timestamp = stm_now();
            current.modifier = e->modifiers;
            break;
        case SAPP_EVENTTYPE_MOUSE_UP:
        case SAPP_EVENTTYPE_MOUSE_DOWN:
            current.buttons[e->mouse_button].down = e->type == SAPP_EVENTTYPE_MOUSE_DOWN;
            current.buttons[e->mouse_button].timestamp = stm_now();
            break;
        case SAPP_EVENTTYPE_MOUSE_MOVE:
            current.cursor.x = e->mouse_x;
            current.cursor.y = e->mouse_y;
            break;
        case SAPP_EVENTTYPE_MOUSE_SCROLL:
            current.scroll.x = e->scroll_x;
            current.scroll.y = e->scroll_y;
            break;
        default:
            current.modifier = e->modifiers;
            break;
    }
}

void sokol_input_update(void) {
    memcpy(&prev, &current, sizeof(input_t));
    current.scroll.x = current.scroll.y = 0.f;
}

int sapp_is_key_down(int key) {
    return current.keys[key].down == 1;
}

int sapp_is_key_held(int key) {
    return sapp_is_key_down(key) && stm_sec(stm_since(current.keys[key].timestamp)) > DEFAULT_KEY_HOLD_DELAY;
}

int sapp_was_key_pressed(int key) {
    return sapp_is_key_down(key) && !prev.keys[key].down;
}

int sapp_was_key_released(int key) {
    return !sapp_is_key_down(key) && prev.keys[key].down;
}

int sapp_are_keys_down(int n, ...) {
    va_list args;
    va_start(args, n);
    int result = 1;
    for (int i = 0; i < n; i++)
        if (!current.keys[va_arg(args, int)].down) {
            result = 0;
            goto BAIL;
        }
BAIL:
    va_end(args);
    return result;
}

int sapp_any_keys_down(int n, ...) {
    va_list args;
    va_start(args, n);
    int result = 0;
    for (int i = 0; i < n; i++)
        if (current.keys[va_arg(args, int)].down) {
            result = 1;
            goto BAIL;
        }
BAIL:
    va_end(args);
    return result;
}

int sapp_is_button_down(int button) {
    return current.buttons[button].down;
}

int sapp_is_button_held(int button) {
    return sapp_is_button_down(button) && stm_sec(stm_since(current.buttons[button].timestamp)) > DEFAULT_KEY_HOLD_DELAY;
}

int sapp_was_button_pressed(int button) {
    return sapp_is_button_down(button) && !prev.buttons[button].down;
}

int sapp_was_button_released(int button) {
    return !sapp_is_button_down(button) && prev.buttons[button].down;
}

int sapp_are_buttons_down(int n, ...) {
    va_list args;
    va_start(args, n);
    int result = 1;
    for (int i = 0; i < n; i++)
        if (!current.buttons[va_arg(args, int)].down) {
            result = 0;
            goto BAIL;
        }
BAIL:
    va_end(args);
    return result;
}

int sapp_any_buttons_down(int n, ...) {
    va_list args;
    va_start(args, n);
    int result = 0;
    for (int i = 0; i < n; i++)
        if (current.buttons[va_arg(args, int)].down) {
            result = 1;
            goto BAIL;
        }
BAIL:
    va_end(args);
    return result;
}

int sapp_modifier_check_only(int n, ...) {
    va_list args;
    va_start(args, n);
    int result = 0;
    for (int i = 0; i < n; i++)
        result |= va_arg(args, int);
    va_end(args);
    return result == current.modifier;
}

int sapp_modifier_check_each(int n, ...) {
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++)
        if (!sapp_modifier_check_in(va_arg(args, int)))
            return 0;
    va_end(args);
    return 1;
}

int sapp_modifier_check_any(int n, ...) {
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++)
        if (sapp_modifier_check_in(va_arg(args, int)))
            return 1;
    va_end(args);
    return 0;
}

int sapp_modifier_check_in(int modifier) {
    return current.modifier & modifier;
}

int sapp_any_modifiers(void) {
    return current.modifier != 0;
}

int sapp_has_mouse_move(void) {
    return current.cursor.x != prev.cursor.x || current.cursor.y != prev.cursor.y;
}

int sapp_cursor_x(void) {
    return current.cursor.x;
}

int sapp_cursor_y(void) {
    return current.cursor.y;
}

int sapp_cursor_delta_x(void) {
    return current.cursor.x - prev.cursor.x;
}

int sapp_cursor_delta_y(void) {
    return current.cursor.y - prev.cursor.y;
}

int sapp_check_scrolled(void) {
    return current.scroll.x != 0 || current.scroll.y != 0;
}

float sapp_scroll_x(void) {
    return current.scroll.x;
}

float sapp_scroll_y(void) {
    return current.scroll.y;
}

#endif // SOKOL_HELPER_IMPL
