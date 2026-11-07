#include <iostream>

struct Ball
{
	Color color = WHITE;
	float radius = 15.0f;
	Vector2 position = { GetScreenWidth() / 2.0f, GetScreenHeight() - radius - 10.0f - 30.0f};
	Vector2 direction = { 6.0f, -4.8f };

	void Draw()
	{
		DrawCircle(
			position.x,
			position.y,
			radius,
			color
		);
	}

	void Update(Bricks& bricks, Paddle& paddle, Sound& hit, bool& active)
	{
		position.x += direction.x;
		position.y += direction.y;
		std::cout << direction.x << ", " << direction.y << std::endl;

		if (position.x <= 0 + radius || position.x >= GetScreenWidth() - radius) { direction.x *=  -1; PlaySound(hit); }
		if (position.y <= 0 + radius) { direction.y *= -1; PlaySound(hit); position.y += radius; }

		if (
			position.x + radius >= paddle.paddlePosition.x &&
			position.x - radius <= paddle.paddlePosition.x + paddle.paddleWidth &&

			position.y + radius >= paddle.paddlePosition.y &&
			position.y - radius <= paddle.paddlePosition.y + paddle.paddleHeight
			)
		{
			float paddleCenter = paddle.paddlePosition.x + paddle.paddleWidth / 2.0f;

			float hitPosition = (position.x - paddleCenter) / (paddle.paddleWidth / 2.0f);

			direction.x = hitPosition * 15;
			direction.y *= -1;
			direction.x *= -1;
			position.y = paddle.paddlePosition.y - radius;

			std::cout << "Hit paddle" << std::endl;

			PlaySound(hit);
		}

		if (position.y > GetScreenHeight() + 50)
		{

			active = false;
			position = { GetScreenWidth() / 2.0f, GetScreenHeight() - radius - 10.0f - 30.0f };
			paddle.paddlePosition = { ((float)GetScreenWidth() / 2.0f) - (paddle.paddleWidth / 2.0f), ((float)GetScreenHeight()) - paddle.paddleHeight - 10.0f };
		}
	
	}

};