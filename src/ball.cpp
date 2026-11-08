#include "raylib.h"
#include "headers/bricks.hpp"
#include "headers/ball.hpp"
#include "headers/paddle.hpp"
#include <vector>

extern std::vector<Bricks> brick;
extern std::vector<Balls> ball;

void DrawBall(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active, Balls& balls)
{


	for (auto& i : ball)
	{
		DrawCircle(
			i.position.x,
			i.position.y,
			i.radius,
			i.color
		);
	}
}

void UpdateBall(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active, Balls& balls)
{
	for (auto& i : ball)
	{
		i.position.x += i.direction.x * GetFrameTime();
		i.position.y += i.direction.y * GetFrameTime();
		std::cout << i.direction.x << ", " << i.direction.y << std::endl;

		if (i.position.x <= 0 + i.radius || i.position.x >= GetScreenWidth() - i.radius) { i.direction.x *= -1; PlaySound(hit); }
		if (i.position.y <= 0 + i.radius) { i.direction.y *= -1; PlaySound(hit); i.position.y += i.radius; }

		if (
			i.position.x + i.radius >= paddle.paddlePosition.x &&
			i.position.x - i.radius <= paddle.paddlePosition.x + paddle.paddleWidth &&

			i.position.y + i.radius >= paddle.paddlePosition.y &&
			i.position.y - i.radius <= paddle.paddlePosition.y + paddle.paddleHeight
			)
		{
			float paddleCenter = paddle.paddlePosition.x + paddle.paddleWidth / 2.0f;

			float hitPosition = (i.position.x - paddleCenter) / (paddle.paddleWidth / 2.0f);

			float totalSpeed = 768.0f;

			i.direction.x = hitPosition * totalSpeed * 0.8f;
			i.direction.y *= -1;
			i.direction.x *= -1;
			i.position.y = paddle.paddlePosition.y - i.radius;

			std::cout << "Hit paddle" << std::endl;

			PlaySound(hit);
		}


		for (size_t i = 0; i < ball.size(); ) { 

			if (ball[i].position.y > GetScreenHeight() + 50) { 
				ball.erase(ball.begin() + i);

				if (ball.empty())
				{
					active = false;
					paddle.paddlePosition = { ((float)GetScreenWidth() / 2.0f) - (paddle.paddleWidth / 2.0f), ((float)GetScreenHeight()) - paddle.paddleHeight - 10.0f };
				}
			}
			else {
				i++; 
			}
		}

	}

}