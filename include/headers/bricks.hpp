#pragma once
#include "raylib.h"
#include <vector>

struct Bricks
{
	Color color = RED;
	float width = 110.0f;
	float height = 30.0f;
	float padding = 12.0f;
	Vector2 position;
	Rectangle brickRectangle;
	bool active = true;
	bool ballPowerup = false;
	bool air = false;

};

