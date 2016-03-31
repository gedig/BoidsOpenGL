#include "EventHandler.hpp"

void EventHandler::Update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			AddQuitEvent();
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			//HandleKeyBoard(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			//HandleMouseButton(event);
			break;
		case SDL_MOUSEMOTION:
			//HandleMouseMove(event);
			break;
		default:
			break;
		}
	}
}

void EventHandler::AddQuitEvent() {
	quit = true;
	events.emplace_back(Event(EventType::Quit));
}


std::vector<Event> EventHandler::GetEvents() { return events; }

void EventHandler::ClearEvents() { events.clear(); }