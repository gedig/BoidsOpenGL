#include "EventHandler.hpp"

void EventHandler::Update() {
	reset = quit = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			AddEvent(EventType::Quit);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			HandleKeyBoard(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			//HandleMouseButton(event);
			break;
		case SDL_MOUSEMOTION:
			//HandleMouseMove(event);
			break;
		case SDL_MOUSEWHEEL:
			HandleMouseWheel(event);
			break;
		default:
			break;
		}
	}
}

void EventHandler::HandleKeyBoard(SDL_Event &_event) {
	switch (_event.key.keysym.sym) {
	case SDLK_w:
	case SDLK_UP:
		// TODO-DG: If shift is held, pan instead of rotate
		AddEvent(EventType::CameraRotation, EventAction::Up);
		break;
	case SDLK_a:
	case SDLK_LEFT:
		AddEvent(EventType::CameraRotation, EventAction::Left);
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		AddEvent(EventType::CameraRotation, EventAction::Right);
		break;
	case SDLK_s:
	case SDLK_DOWN:
		AddEvent(EventType::CameraRotation, EventAction::Down);
		break;
	case SDLK_r:
		ClearEvents();
		AddEvent(EventType::Reset);
	default:
		break;
	}
}

void EventHandler::HandleMouseWheel(SDL_Event & _event)
{
	if (_event.wheel.y < 0) {
		events.emplace_back(Event(EventType::CameraDolly, EventAction::Down));
	}
	else if (_event.wheel.y > 0) {
		events.emplace_back(Event(EventType::CameraDolly, EventAction::Up));
	}
}

void EventHandler::AddEvent(EventType _type, EventAction _action) {
	if (_type == EventType::Quit) {
		quit = true;
	}
	else if (_type == EventType::Reset) {
		reset = true;
	}
	
	events.emplace_back(Event(_type, _action));
}


std::vector<Event> EventHandler::GetEvents() { return events; }

void EventHandler::ClearEvents() { events.clear(); }