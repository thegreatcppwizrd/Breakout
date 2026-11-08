#include "headers/paddle.hpp"
#include "headers/bricks.hpp"
#include "headers/ball.hpp"
#include <iostream>
#include <algorithm>

void DrawBall(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active, Balls& balls);
void UpdateBall(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active, Balls& balls);

std::vector<Bricks> brick;
std::vector<Balls> ball;

void UpdateBrick(Balls& balls, Sound& hit, Paddle& paddle)
{
	for (auto& i : brick)
	{
		if (!i.air)
		{
			for (auto& j : ball)
			{
				if (!i.active) continue;

				if (
					j.position.x + j.radius >= i.position.x &&
					j.position.x - j.radius <= i.position.x + i.width &&

					j.position.y + j.radius >= i.position.y &&
					j.position.y - j.radius <= i.position.y + i.height
					)
				{

					if (j.direction.y < 0)
					{
						j.position.y = i.position.y + i.height + j.radius;
					}
					else if (j.direction.y > 0)
					{
						j.position.y = i.position.y - j.radius;
					}

					j.direction.y *= -1;

					std::cout << "Hit brick" << std::endl;
					PlaySound(hit);
					i.active = false;

					if (i.ballPowerup)
					{

						ball.push_back({
							j.color,
							j.radius,
							{ i.position.x + i.width / 2.0f, i.position.y + i.height / 2.0f },
							{
								j.direction.x,
								j.direction.y
							}
							});
					}


					break;

				}
			}
		}
	}
}


void DrawBrick()
{
	for (auto& i : brick)	
	{
		if (i.active)
		{
			if (!i.air)
			{
				DrawRectangleRounded(i.brickRectangle, 0.5, 0, i.color);
			}

			if (i.ballPowerup)
			{
				DrawCircle(
					i.position.x + i.width / 2,
					i.position.y + i.height / 2,
					i.height / 2 - 5,
					{ 0, 0, 0, 80 }
					);

				// TraceLog(LOG_INFO, "Ball Pos: %f, %f", i.position.x + i.width / 2, i.position.y + i.height / 2);
			}
		}
	}
}
 
void PlaceBricks(Bricks& bricks)
{
	int ammountX = GetScreenWidth() / (bricks.width + bricks.padding);
	int ammountY = 10;

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


			Color pallet[10] = {
				RED,
				YELLOW,
				ORANGE,
				BLUE,
				DARKBLUE,
				GREEN,
				DARKGREEN,
				PINK,
				MAGENTA,
				VIOLET
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

			brick.back().ballPowerup = GetRandomValue(1, 4) == 1 ? true : false;
			brick.back().air = (i + j) % GetRandomValue(2, 7) == 0 ? true : false;

			if (brick.back().air)
			{
				brick.pop_back();
			}
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
	Balls balls;

	bool active = false;

	ball.push_back({
		balls.color,
		balls.radius,
		balls.position,
		balls.direction
		});

	while (!WindowShouldClose())
	{


		BeginDrawing();
		ClearBackground(BLACK);
		DrawBrick();

		 
		if (active)
		{
			DrawBall(bricks, paddle, hit, active, balls);
			UpdateBall(bricks, paddle, hit, active, balls);
			paddle.Update();
			UpdateBrick(balls, hit, paddle);

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
				paddle.paddlePosition = { ((float)GetScreenWidth() / 2.0f) - (paddle.paddleWidth / 2.0f), ((float)GetScreenHeight()) - paddle.paddleHeight - 10.0f };

				for (size_t i = 0; i < ball.size(); ) {

					ball.erase(ball.begin() + i);
				}
			}

			
		}
		else
		{
			brick.clear();
			std::cout << "Draw text" << std::endl;
			const char* text = "Press the up arrow key to start the game";
			int fontSize = 25;
			DrawText(
				text,
				balls.position.x - MeasureText(text, fontSize) / 2,
				balls.position.y - 50 - balls.radius,
				fontSize,
				WHITE


			);

			if (IsKeyPressed(KEY_UP))
			{
				PlaceBricks(bricks);
				active = true;
				std::cout << "Start" << std::endl;
				ball.push_back({ balls.color, balls.radius, balls.position, balls.direction });

			}
		}

		


		paddle.Draw();
		// std::cout << paddle.paddlePosition.x << paddle.paddlePosition.y << std::endl;

		EndDrawing();
	}

	    CloseWindow();
}
