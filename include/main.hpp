#ifndef INCLUDE_MAIN_HPP
#define INCLUDE_MAIN_HPP

#pragma once

#include <vector>

#include "Boid.hpp"
#include "Camera.hpp"
#include "EventHandler.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"


#define TIME_MOD 1.0f

#define NUM_BOIDS 600
#define INITIAL_DISTANCE 50.0f
#define INITIAL_HEIGHT 30.0f
#define SEPARATION_DISTANCE 8.0f

#define INITIAL_CAMERA_DISTANCE 150.0f
#define CAMERA_DOLLY_SPEED 25.0f
#define CAMERA_MOVE_THRESHOLD 1.0f
#define CAMERA_SPEED_MOD 10.0f
#define CAMERA_ROTATE_SPEED 2.0f
#define CAMERA_LOCK_TIME 10.0f

#define BOUNDS_BOUNCE 0.8f
// Note: Other constants related to boid rules are in Boid.hpp

void Reset();
void Update();
void Render();

Camera camera;
GLfloat cameraFlockDistance;
GLfloat cameraVerticalLockTime;

EventHandler eventHandler;
Grid floorGrid;
Renderer renderer;

GLint64 prevTime = 0;

// Boids Vars:
Model boidModel;
Boid boids[NUM_BOIDS];

#endif