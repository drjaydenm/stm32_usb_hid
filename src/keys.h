#ifndef __KEYS_H
#define __KEYS_H

#include <stdint.h>

#define KeyType uint8_t

// Take a look at Page 53 https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
KeyType KEY_NO_EVENT = 0x00;
KeyType KEY_ERROR_ROLL_OVER = 0x01;
KeyType KEY_POST_FAIL = 0x02;
KeyType KEY_ERROR_UNDEFINED = 0x03;

KeyType KEY_A = 0x04;
KeyType KEY_B = 0x05;
KeyType KEY_C = 0x06;
KeyType KEY_D = 0x07;
KeyType KEY_E = 0x08;
KeyType KEY_F = 0x09;
KeyType KEY_G = 0x0A;
KeyType KEY_H = 0x0B;
KeyType KEY_I = 0x0C;
KeyType KEY_J = 0x0D;
KeyType KEY_K = 0x0E;
KeyType KEY_L = 0x0F;
KeyType KEY_M = 0x10;
KeyType KEY_N = 0x11;
KeyType KEY_O = 0x12;
KeyType KEY_P = 0x13;
KeyType KEY_Q = 0x14;
KeyType KEY_R = 0x15;
KeyType KEY_S = 0x16;
KeyType KEY_T = 0x17;
KeyType KEY_U = 0x18;
KeyType KEY_V = 0x19;
KeyType KEY_W = 0x1A;
KeyType KEY_X = 0x1B;
KeyType KEY_Y = 0x1C;
KeyType KEY_Z = 0x1D;

KeyType KEY_1 = 0x1E;
KeyType KEY_2 = 0x1F;
KeyType KEY_3 = 0x20;
KeyType KEY_4 = 0x21;
KeyType KEY_5 = 0x22;
KeyType KEY_6 = 0x23;
KeyType KEY_7 = 0x24;
KeyType KEY_8 = 0x25;
KeyType KEY_9 = 0x26;
KeyType KEY_0 = 0x27;

KeyType KEY_ENTER = 0x28;
KeyType KEY_ESC = 0x29;
KeyType KEY_BACKSPACE = 0x2A;
KeyType KEY_TAB = 0x2B;
KeyType KEY_SPACE = 0x2C;
KeyType KEY_MINUS = 0x2D;
KeyType KEY_EQUAL = 0x2E;
KeyType KEY_LEFTBRACE = 0x2F;
KeyType KEY_RIGHTBRACE = 0x30;
KeyType KEY_BACKSLASH = 0x31;
KeyType KEY_HASHTILDE = 0x32;
KeyType KEY_SEMICOLON = 0x33;
KeyType KEY_APOSTROPHE = 0x34;
KeyType KEY_GRAVE = 0x35;
KeyType KEY_COMMA = 0x36;
KeyType KEY_DOT = 0x37;
KeyType KEY_SLASH = 0x38;
KeyType KEY_CAPSLOCK = 0x39;

KeyType KEY_F1 = 0x3A;
KeyType KEY_F2 = 0x3B;
KeyType KEY_F3 = 0x3C;
KeyType KEY_F4 = 0x3D;
KeyType KEY_F5 = 0x3E;
KeyType KEY_F6 = 0x3F;
KeyType KEY_F7 = 0x40;
KeyType KEY_F8 = 0x41;
KeyType KEY_F9 = 0x42;
KeyType KEY_F10 = 0x43;
KeyType KEY_F11 = 0x44;
KeyType KEY_F12 = 0x45;

KeyType KEY_SYSRQ = 0x46;
KeyType KEY_SCROLLLOCK = 0x47;
KeyType KEY_PAUSE = 0x48;
KeyType KEY_INSERT = 0x49;
KeyType KEY_HOME = 0x4A;
KeyType KEY_PAGEUP = 0x4B;
KeyType KEY_DELETE = 0x4C;
KeyType KEY_END = 0x4D;
KeyType KEY_PAGEDOWN = 0x4E;
KeyType KEY_RIGHT = 0x4F;
KeyType KEY_LEFT = 0x50;
KeyType KEY_DOWN = 0x51;
KeyType KEY_UP = 0x52;

KeyType KEY_NUMLOCK = 0x53;
KeyType KEY_KEYPAD_SLASH = 0x54;
KeyType KEY_KEYPAD_ASTERISK = 0x55;
KeyType KEY_KEYPAD_MINUS = 0x56;
KeyType KEY_KEYPAD_PLUS = 0x57;
KeyType KEY_KEYPAD_ENTER = 0x58;
KeyType KEY_KEYPAD_1 = 0x59;
KeyType KEY_KEYPAD_2 = 0x5A;
KeyType KEY_KEYPAD_3 = 0x5B;
KeyType KEY_KEYPAD_4 = 0x5C;
KeyType KEY_KEYPAD_5 = 0x5D;
KeyType KEY_KEYPAD_6 = 0x5E;
KeyType KEY_KEYPAD_7 = 0x5F;
KeyType KEY_KEYPAD_8 = 0x60;
KeyType KEY_KEYPAD_9 = 0x61;
KeyType KEY_KEYPAD_0 = 0x62;
KeyType KEY_KEYPAD_DOT = 0x63;

KeyType KEY_102ND = 0x64;
KeyType KEY_COMPOSE = 0x65;
KeyType KEY_POWER = 0x66;
KeyType KEY_KEYPAD_EQUAL = 0x67;

KeyType KEY_F13 = 0x68;
KeyType KEY_F14 = 0x69;
KeyType KEY_F15 = 0x6A;
KeyType KEY_F16 = 0x6B;
KeyType KEY_F17 = 0x6C;
KeyType KEY_F18 = 0x6D;
KeyType KEY_F19 = 0x6E;
KeyType KEY_F20 = 0x6F;
KeyType KEY_F21 = 0x70;
KeyType KEY_F22 = 0x71;
KeyType KEY_F23 = 0x72;
KeyType KEY_F24 = 0x73;

KeyType KEY_LEFTCTRL = 0xE0;
KeyType KEY_LEFTSHIFT = 0xE1;
KeyType KEY_LEFTALT = 0xE2;
KeyType KEY_LEFTMETA = 0xE3;
KeyType KEY_RIGHTCTRL = 0xE4;
KeyType KEY_RIGHTSHIFT = 0xE5;
KeyType KEY_RIGHTALT = 0xE6;
KeyType KEY_RIGHTMETA = 0xE7;

#endif
