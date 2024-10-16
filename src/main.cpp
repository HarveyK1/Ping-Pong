#include "raylib.h"
#include <iostream>

class Ball
{
public:
	float x{}, y{};
	float speedX{}, speedY{};
	float radius{};

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, WHITE);
	}

	void BallReset()
	{

	}
};

class Paddle
{
public:
	float x{}, y{};
	float speedY{};
	float width{}, height{};

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, width, height };
	}

	void Draw() 
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

int main()
{

	InitWindow(800, 600, "Ping Pong");
	SetWindowState(FLAG_VSYNC_HINT);
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5.0f;
	ball.speedX = 300;
	ball.speedY = 300;

	Paddle leftPaddle;
	leftPaddle.x = 20;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speedY = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 20;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speedY = 500;

	const char* winnerText{ nullptr };
	const char* restartText{ nullptr };
	const char* scoreText{ nullptr };
	int rightSideScore{};
	int leftSideScore{};

	while (!WindowShouldClose())
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();


		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (IsKeyDown(KEY_W))
		{
			leftPaddle.y -= leftPaddle.speedY * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftPaddle.y += leftPaddle.speedY * GetFrameTime();
		}
		if (IsKeyDown(KEY_K))
		{
			rightPaddle.y -= rightPaddle.speedY * GetFrameTime();
		}
		if (IsKeyDown(KEY_M))
		{
			rightPaddle.y += rightPaddle.speedY * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1;
			}
		}
		if (ball.x < 0)
		{
			winnerText = "Right Side Wins!\n";
			restartText = "Press Spacebar to restart!\n";
			rightSideScore += 1;
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Side Wins!\n";
			restartText = "Press Spacebar to restart!\n";
			leftSideScore += 1;
		}
		if (winnerText && restartText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			winnerText = nullptr;
			restartText = nullptr;
		}

		BeginDrawing();
			ClearBackground(BLACK);
			DrawFPS(5, 5);

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();

			if (winnerText)
			{
				int winnerTextWidth = MeasureText(winnerText, 80);
				DrawText(winnerText, GetScreenWidth() / 2 - winnerTextWidth / 2, GetScreenHeight() / 2 - 30, 80, YELLOW);
			}
			if (restartText)
			{
				int restartTextWidth = MeasureText(restartText, 20);
				DrawText(restartText, GetScreenWidth() / 2 - restartTextWidth / 2, GetScreenHeight() / 2 - -200, 20, WHITE);
			}
			
			int scoreTextWidth = MeasureText(scoreText, 50);
			DrawText(TextFormat("Score: %i", rightSideScore), 10, 20, 20, WHITE);
			DrawText(TextFormat("Score: %i", leftSideScore), (GetScreenWidth() + 10) - MeasureText(TextFormat("Score: %i", leftSideScore), 25), 20, 20, WHITE);

		EndDrawing();
		CloseWindow();
	}
	return 0;
}