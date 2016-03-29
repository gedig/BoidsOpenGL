#ifndef INCLUDE_EVENTHANDLER_HPP
#define INCLUDE_EVENTHANDLER_HPP

#pragma once

#include <SDL.h>

#include<map>
#include <vector>

enum class ButtonEventType {
	Pressed,
	Released,
};

enum class ButtonState {
	Up,
	Down,
};

struct KeyboardEvent {
	ButtonEventType eventType;
	SDL_Keycode key;
};

enum class MouseButton {
	Left,
	Middle,
	Right,
	Unknown,
};

struct MouseMotionEvent {
	SDL_Point newPos;
	SDL_Point relativePos;
};

struct MouseButtonEvent {
	ButtonEventType eventType;
	MouseButton button;
};

enum class EventType {
	Keyboard,
	MouseButton,
	MouseMotion,
	Quit,
};

struct Event {
	Event(EventType _type) : type(_type) {}
	EventType type;

	KeyboardEvent keyboard;
	MouseMotionEvent mouseMove;
	MouseButtonEvent mouseButton;
};

class EventHandler {
public:
	EventHandler() : quit(false) {}

	void Update();
	void ClearEvents();
	std::vector<Event> GetEvents();

	ButtonState GetKeyState(SDL_Keycode key) const;
	bool IsKeyDown(SDL_Keycode key) const;

	ButtonState GetMouseButtonState(MouseButton button) const;
	bool IsMouseButtonDown(MouseButton button) const;

	SDL_Point GetMousePoint() const;

	bool Quit() { return quit; }

private:
	void HandleKeyBoard(const SDL_Event &event);
	void HandleMouseButton(const SDL_Event &event);
	void HandleMouseMove(const SDL_Event &event);

	void AddQuitEvent();
	void AddKeyboardEvent(const SDL_Event &event);
	void AddMouseEvent(const SDL_Event &event);

	Event CreateKeyboardEvent(const SDL_Event &event) const;
	Event CreateMouseEvent(const SDL_Event &event) const;

	// SDL uses #defines for mouse button types internal. Change this to enum classes for better safety
	MouseButton ConvertMouseButtonToEnum(uint8_t SDLButtonID) const;
	uint8_t ConvertMouseButtonToID(MouseButton button) const;

	ButtonState ConvertButtonStateFromSDL(uint32_t keyEventID, EventType type) const;
	uint32_t ConvertButtonStateToSDL(ButtonState button, EventType type) const;

	SDL_Point mousePoint;
	std::vector<Event> events;

	std::map<SDL_Keycode, ButtonState> keyCode;

	std::map<MouseButton, ButtonState> mouseButton;

	bool quit;
};

#endif