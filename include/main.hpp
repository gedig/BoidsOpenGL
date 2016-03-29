#ifndef INCLUDE_MAIN_HPP
#define INCLUDE_MAIN_HPP

#pragma once

#include <vector>

#include "Camera.hpp"
#include "EventHandler.hpp"
#include "Model.hpp"
#include "Renderer.hpp"

void Reset();
void Update();
void Render();

Camera camera;
EventHandler eventHandler;
Renderer renderer;

std::vector<Model> modelList;

#endif