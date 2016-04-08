#ifndef INCLUDE_EVENTHANDLER_HPP
#define INCLUDE_EVENTHANDLER_HPP

#pragma once

#include <SDL.h>

#include<map>
#include <vector>

enum class EventAction {
	None,
	Left,
	Right,
	Up,
	Down,
};
enum class EventType {
	// If this class acts as action abstraction (for remappable controls later)
	//	then external classes don't need to know what was actually pressed, just what to do.
	//Keyboard,
	//MouseButton,
	//MouseMotion,
	CameraPan,
	CameraRotation,
	Quit,
};

struct Event {
	Event(EventType _type) : type(_type) {}
	Event(EventType _type, EventAction _action) : type(_type), action(_action) {}
	EventType type;
	EventAction action;
};

class EventHandler {
public:
	EventHandler() : quit(false) {}

	void Update();
	void ClearEvents();
	std::vector<Event> GetEvents();

	bool Quit() { return quit; }

private:
	void AddEvent(EventType _type, EventAction _action = EventAction::None);
	void HandleKeyBoard(SDL_Event &_event);

	SDL_Point mousePoint;
	std::vector<Event> events;

	bool quit;
};

#endif