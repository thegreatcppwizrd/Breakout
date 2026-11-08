#include <iostream>
#include <vector>

struct Balls
{
	Color color = WHITE;
	float radius = 15.0f;
	Vector2 position = { GetScreenWidth() / 2.0f, GetScreenHeight() - radius - 10.0f - 30.0f};
	Vector2 direction = { 600.0f, -480.0f };


};

