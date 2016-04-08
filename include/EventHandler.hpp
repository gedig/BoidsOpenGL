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
	// This class abstracts actions (for remappable controls later)
	// external classes don't need to know what was actually pressed, just what to do.
	CameraDolly,
	CameraPan,
	CameraRotation,
	Reset,
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
	bool Reset() { return reset; }

private:
	void AddEvent(EventType _type, EventAction _action = EventAction::None);
	void HandleKeyBoard(SDL_Event &_event);
	void HandleMouseWheel(SDL_Event &_event);

	SDL_Point mousePoint;
	std::vector<Event> events;

	bool quit;
	bool reset;
};

#endif