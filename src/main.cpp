#include "headers/paddle.hpp"
#include "headers/bricks.hpp"
#include <iostream>

void DrawBrick()
{
	for (auto& i : brick)	
	{
		DrawRectangleRounded(i.brickRectangle, 0.5, 0, i.color);
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

			brick[j].active = true;

		}
	}
}

int main()
{
	InitWindow(1024, 768, "Breakout");
	SetTargetFPS(60);

	Paddle paddle;
	Bricks bricks;

	PlaceBricks(bricks);


	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);
		

		DrawBrick();
		paddle.Draw();
		paddle.Update();

		// std::cout << paddle.paddlePosition.x << paddle.paddlePosition.y << std::endl;

		EndDrawing();
	}

	CloseWindow();
}
