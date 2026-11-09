#include "headers/paddle.hpp"
#include "headers/bricks.hpp"
#include "headers/ball.hpp"
#include <iostream>
#include <algorithm>

void DrawBall(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active, Balls& balls);
void UpdateBall(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active, Balls& balls);

std::vector<Bricks> brick;
std::vector<Balls> ball;

void UpdateBrick(Balls& balls, Sound& hit, Paddle& paddle, bool& timerStarted, float& timer)
{
	for (auto& i : brick)
	{
		if (!i.air)
		{
			for (auto& j : ball)
			{
				if (!i.active) continue;

				if (i.solid && !i.ballPowerup && !i.expand)
				{
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


					}
				}
				else
				{
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

						if (i.ballPowerup && ball.size() < 3) // 
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




						if (i.expand)
						{
							paddle.paddleWidth = 200.0f;
							if (timerStarted)
							{
								timer = 0.0f;
							}
							else
							{
								timerStarted = true;
							}
						}




					}
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


			if (i.expand && !i.ballPowerup)
			{
				float width = 50;
				float height = 15;

				DrawRectangleRounded(
					{
						i.position.x + (i.width / 2) - (width / 2),  // Centers horizontally
						i.position.y + (i.height / 2) - (height / 2), // Centers vertically
						width,
						height
					},
					10.0f,
					10,
					{ 0, 0, 0, 80 }
				);
			}

			if (i.solid)
			{
				DrawRectangleRounded(
					{
						i.position.x,
						i.position.y,
						i.width,
						i.height
					},
					0.5f,
					0,
					{ 46, 255, 213, 255 }
				);
			}
		} // FIXED: Added missing closing brace for if (i.active)
	} // FIXED: Added missing closing brace for for (auto& i : brick)
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

			brick.back().air = (i + j) % GetRandomValue(2, 7) == 0 ? true : false;

			brick.back().expand = GetRandomValue(1, 100) <= 10; // normal is 10
			brick.back().ballPowerup = GetRandomValue(1, 100) <= 15; // normal is 15
			brick.back().solid = GetRandomValue(1, 100) <= 20; // normal is 20

			if (brick.back().solid && brick.back().ballPowerup)
			{
				brick.back().solid = false;
			}
			if (brick.back().solid && brick.back().expand)
			{
				brick.back().solid = false;
			}
			if (brick.back().solid && brick.back().air)
			{
				brick.back().solid = false;
			}

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

	float timer = 0.0f;
	bool timerStarted = false;

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
			UpdateBrick(balls, hit, paddle, timerStarted, timer);

			bool allDestroyed = std::none_of(brick.begin(), brick.end(), [](const Bricks& b) {
				return (b.active && !b.solid);
				});


			if (timerStarted)
			{
				timer += GetFrameTime();

				if (timer >= 5.0f)
				{
					timerStarted = false;
					timer = 0.0f;
					paddle.paddleWidth = 130.0f;
				}
			}



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

			paddle.paddleWidth = 130.0f;

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
