#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard;

#include <GL/SDL.h>

class Keyboard {

public:
	Keyboard();

	void update();

	bool isKeyDown(int key);

	bool wasKeyPressed(int key);

	bool wasKeyReleased(int key);

	static const int KEY_0 = SDL_SCANCODE_0;
	static const int KEY_1 = SDL_SCANCODE_1;
	static const int KEY_2 = SDL_SCANCODE_2;
	static const int KEY_3 = SDL_SCANCODE_3;
	static const int KEY_4 = SDL_SCANCODE_4;
	static const int KEY_5 = SDL_SCANCODE_5;
	static const int KEY_6 = SDL_SCANCODE_6;
	static const int KEY_7 = SDL_SCANCODE_7;
	static const int KEY_8 = SDL_SCANCODE_8;
	static const int KEY_9 = SDL_SCANCODE_9;

	static const int KEY_A = SDL_SCANCODE_A;
	static const int KEY_B = SDL_SCANCODE_B;
	static const int KEY_C = SDL_SCANCODE_C;
	static const int KEY_D = SDL_SCANCODE_D;
	static const int KEY_E = SDL_SCANCODE_E;
	static const int KEY_F = SDL_SCANCODE_F;
	static const int KEY_G = SDL_SCANCODE_G;
	static const int KEY_H = SDL_SCANCODE_H;
	static const int KEY_I = SDL_SCANCODE_I;
	static const int KEY_J = SDL_SCANCODE_J;
	static const int KEY_K = SDL_SCANCODE_K;
	static const int KEY_L = SDL_SCANCODE_L;
	static const int KEY_M = SDL_SCANCODE_M;
	static const int KEY_N = SDL_SCANCODE_N;
	static const int KEY_O = SDL_SCANCODE_O;
	static const int KEY_P = SDL_SCANCODE_P;
	static const int KEY_Q = SDL_SCANCODE_Q;
	static const int KEY_R = SDL_SCANCODE_R;
	static const int KEY_S = SDL_SCANCODE_S;
	static const int KEY_T = SDL_SCANCODE_T;
	static const int KEY_U = SDL_SCANCODE_U;
	static const int KEY_V = SDL_SCANCODE_V;
	static const int KEY_W = SDL_SCANCODE_W;
	static const int KEY_X = SDL_SCANCODE_X;
	static const int KEY_Y = SDL_SCANCODE_Y;
	static const int KEY_Z = SDL_SCANCODE_Z;

	static const int KEY_RETURN = SDL_SCANCODE_RETURN;
	static const int KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
	static const int KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE;
	static const int KEY_TAB = SDL_SCANCODE_TAB;
	static const int KEY_SPACE = SDL_SCANCODE_SPACE;

	static const int KEY_MINUS = SDL_SCANCODE_MINUS;
	static const int KEY_EQUALS = SDL_SCANCODE_EQUALS;
	static const int KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
	static const int KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET;
	static const int KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON;
	static const int KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE;
	static const int KEY_GRAVE = SDL_SCANCODE_GRAVE; // tilde

	static const int KEY_COMMA = SDL_SCANCODE_COMMA;
	static const int KEY_PERIOD = SDL_SCANCODE_PERIOD;
	static const int KEY_SLASH = SDL_SCANCODE_SLASH;

	static const int KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK;

	static const int KEY_F1 = SDL_SCANCODE_F1;
	static const int KEY_F2 = SDL_SCANCODE_F2;
	static const int KEY_F3 = SDL_SCANCODE_F3;
	static const int KEY_F4 = SDL_SCANCODE_F4;
	static const int KEY_F5 = SDL_SCANCODE_F5;
	static const int KEY_F6 = SDL_SCANCODE_F6;
	static const int KEY_F7 = SDL_SCANCODE_F7;
	static const int KEY_F8 = SDL_SCANCODE_F8;
	static const int KEY_F9 = SDL_SCANCODE_F9;
	static const int KEY_F10 = SDL_SCANCODE_F10;
	static const int KEY_F11 = SDL_SCANCODE_F11;
	static const int KEY_F12 = SDL_SCANCODE_F12;

	static const int KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN;
	static const int KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK;
	static const int KEY_PAUSE = SDL_SCANCODE_PAUSE;
	static const int KEY_INSERT = SDL_SCANCODE_INSERT;
	
	static const int KEY_HOME = SDL_SCANCODE_HOME;
	static const int KEY_PAGEUP = SDL_SCANCODE_PAGEUP;
	static const int KEY_DELETE = SDL_SCANCODE_DELETE;
	static const int KEY_END = SDL_SCANCODE_END;
	static const int KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN;

	static const int KEY_RIGHT = SDL_SCANCODE_RIGHT;
	static const int KEY_LEFT = SDL_SCANCODE_LEFT;
	static const int KEY_DOWN = SDL_SCANCODE_DOWN;
	static const int KEY_UP = SDL_SCANCODE_UP;

	static const int KEY_NUMLOCK = SDL_SCANCODE_NUMLOCKCLEAR;

	static const int KEY_NUMPAD_DIVIDE = SDL_SCANCODE_KP_DIVIDE;
	static const int KEY_NUMPAD_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY;
	static const int KEY_NUMPAD_MINUS = SDL_SCANCODE_KP_MINUS;
	static const int KEY_NUMPAD_PLUS = SDL_SCANCODE_KP_PLUS;
	static const int KEY_NUMPAD_ENTER = SDL_SCANCODE_KP_ENTER;
	static const int KEY_NUMPAD_0 = SDL_SCANCODE_KP_0;
	static const int KEY_NUMPAD_1 = SDL_SCANCODE_KP_1;
	static const int KEY_NUMPAD_2 = SDL_SCANCODE_KP_2;
	static const int KEY_NUMPAD_3 = SDL_SCANCODE_KP_3;
	static const int KEY_NUMPAD_4 = SDL_SCANCODE_KP_4;
	static const int KEY_NUMPAD_5 = SDL_SCANCODE_KP_5;
	static const int KEY_NUMPAD_6 = SDL_SCANCODE_KP_6;
	static const int KEY_NUMPAD_7 = SDL_SCANCODE_KP_7;
	static const int KEY_NUMPAD_8 = SDL_SCANCODE_KP_8;
	static const int KEY_NUMPAD_9 = SDL_SCANCODE_KP_9;
	static const int KEY_NUMPAD_PERIOD = SDL_SCANCODE_KP_PERIOD;

	static const int KEY_LCTRL = SDL_SCANCODE_LCTRL;
	static const int KEY_LSHIFT = SDL_SCANCODE_LSHIFT;
	static const int KEY_LALT = SDL_SCANCODE_LALT;
	static const int KEY_LGUI = SDL_SCANCODE_LGUI; // Windows key / Meta key
	static const int KEY_RCTRL = SDL_SCANCODE_RCTRL;
	static const int KEY_RSHIFT = SDL_SCANCODE_RSHIFT;
	static const int KEY_RALT = SDL_SCANCODE_RALT;
	static const int KEY_RGUI = SDL_SCANCODE_RGUI;

	static const int KEY_MAX = KEY_RGUI + 1;

private:
	const Uint8* keys;

	Uint8 prev[KEY_MAX];
};

#endif