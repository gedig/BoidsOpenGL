#ifndef INCLUDE_MAIN_HPP
#define INCLUDE_MAIN_HPP

#pragma once

#include <vector>

#include "Boid.hpp"
#include "Camera.hpp"
#include "EventHandler.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"

#define NUM_BOIDS 250
#define INITIAL_DISTANCE 50.0f
#define INITIAL_HEIGHT 10.0f
#define SEPARATION_DISTANCE 16.0f

#define MIN_CAMERA_DISTANCE 50.0f
#define MAX_CAMERA_SPEED 7.0f
#define CAMERA_ROTATE_SPEED 2.0f
// Note: Other constants related to rules are in Boid.hpp

void Reset();
void Update();
void Render();

Camera camera;
EventHandler eventHandler;
Grid floorGrid;
Renderer renderer;

GLint64 prevTime = 0;

// Boids Vars:
Model boidModel;
Boid boids[NUM_BOIDS];

#endif