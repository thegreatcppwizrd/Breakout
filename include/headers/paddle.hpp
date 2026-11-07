#pragma once
#include "raylib.h"

struct Paddle
{
	float paddleWidth = 130.0f;
	float paddleHeight = 20.0f;
	Vector2 paddlePosition = { ((float)GetScreenWidth() / 2.0f) - (paddleWidth / 2.0f), ((float)GetScreenHeight()) - paddleHeight - 10.0f };
	int speed = 9;
	int padding = 12;

	Rectangle paddle = { paddlePosition.x, paddlePosition.y, paddleWidth, paddleHeight };

	void Draw()
	{
		Rectangle paddle = { paddlePosition.x, paddlePosition.y, paddleWidth, paddleHeight };
		DrawRectangleRounded(paddle, 1.0f, 0, WHITE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_RIGHT)) { paddlePosition.x += speed; }
		if (IsKeyDown(KEY_LEFT)) { paddlePosition.x -= speed; }

		if (paddlePosition.x <= padding) { paddlePosition.x = padding; }
		if (paddlePosition.x >= GetScreenWidth() - padding - paddleWidth) { paddlePosition.x = GetScreenWidth() - paddleWidth - padding; }
	}
};