#ifndef INCLUDE_EVENTHANDLER_HPP
#define INCLUDE_EVENTHANDLER_HPP

#pragma once

#include <SDL.h>

#include<map>
#include <vector>

enum class EventType {
	Keyboard,
	MouseButton,
	MouseMotion,
	Quit,
};

struct Event {
	Event(EventType _type) : type(_type) {}
	EventType type;
};

class EventHandler {
public:
	EventHandler() : quit(false) {}

	void Update();
	void ClearEvents();
	std::vector<Event> GetEvents();

	bool Quit() { return quit; }

private:

	void AddQuitEvent();

	SDL_Point mousePoint;
	std::vector<Event> events;

	bool quit;
};

#endif