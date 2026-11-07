#include "headers/paddle.hpp"
#include "headers/bricks.hpp"
#include "headers/ball.hpp"
#include <iostream>
#include <algorithm>

void UpdateBrick(Ball& ball, Sound& hit, Paddle& paddle)
{
	for (auto& i : brick)
	{
		if (
			ball.position.x + ball.radius >= i.position.x &&
			ball.position.x - ball.radius <= i.position.x + i.width &&

			ball.position.y + ball.radius >= i.position.y &&
			ball.position.y - ball.radius <= i.position.y + i.height &&

			i.active
			)
		{
			if (ball.direction.y < 0)
			{
				ball.position.y = i.position.y + i.height + ball.radius;
			}
			else if (ball.direction.y > 0)
			{
				ball.position.y = i.position.y - ball.radius;
			}
			ball.direction.y *= -1;

			std::cout << "Hit brick" << std::endl;
			PlaySound(hit);
			i.active = false;

			break; 
		}
	}
}

void DrawBrick()
{
	for (auto& i : brick)	
	{
		if (i.active)
		{
			DrawRectangleRounded(i.brickRectangle, 0.5, 0, i.color);
		}
	}
}
 
void PlaceBricks(Bricks& bricks)
{
	int ammountX = GetScreenWidth() / (bricks.width + bricks.padding);
	int ammountY = 7;

	float totalWidth = ammountX * bricks.width
		+ (ammountX - 1) * bricks.padding;

	float startX = (GetScreenWidth() - totalWidth);
	float startY = bricks.padding;

	for (int i = 0; i < ammountY; i++)
	{
		for (int j = 0; j < ammountX; j++)
		{
			Vector2 position = {
			startX / 2 + (bricks.padding + bricks.width) * j,
		    startY + (bricks.padding + bricks.height) * i
			};

			Color pallet[7] = {
				RED,
				YELLOW,
				ORANGE,
				BLUE,
				DARKBLUE,
				GREEN,
				DARKGREEN,
			};

			brick.push_back({
				pallet[i],
				bricks.width,
				bricks.height,
				bricks.padding,
				position,
				{ position.x, position.y, bricks.width, bricks.height },
				bricks.active
				});


		}
	}
}

int main()
{
	InitWindow(1024, 768, "Breakout");
	SetTargetFPS(60);
	InitAudioDevice();

	Sound hit = LoadSound(RESOURCES_PATH "hit.wav");

	Paddle paddle;
	Bricks bricks;
	Ball ball;

	bool active = false;

	PlaceBricks(bricks);


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawBrick();

		if (IsKeyPressed(KEY_UP))
		{
			active = true;
			std::cout << "Start" << std::endl;
		}
		 
		if (active)
		{
			ball.Update(bricks, paddle, hit, active);
			paddle.Update();
			UpdateBrick(ball, hit, paddle);

			bool allDestroyed = std::none_of(
				brick.begin(),
				brick.end(),
				[](const Bricks& b)
				{
					return b.active;
				}

			);

			if (allDestroyed)
			{
				active = false;
				PlaceBricks(bricks);
				brick.clear();
			}

		}
		else
		{

			std::cout << "Draw text" << std::endl;
			const char* text = "Press the up arrow key to start the game";
			int fontSize = 25;
			DrawText(
				text,
				ball.position.x - MeasureText(text, fontSize) / 2,
				ball.position.y - 50 - ball.radius,
				fontSize,
				WHITE
			);
		}




		paddle.Draw();
		ball.Draw();
		// std::cout << paddle.paddlePosition.x << paddle.paddlePosition.y << std::endl;

		EndDrawing();
	}

	CloseWindow();
}
