#include "raylib.h"

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, WHITE);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

int main() 
{
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	Paddle LeftPaddle;
	LeftPaddle.x = 50;
	LeftPaddle.y = GetScreenHeight() / 2;
	LeftPaddle.width = 10;
	LeftPaddle.height = 100;
	LeftPaddle.speed = 500;

	Paddle RightPaddle;
	RightPaddle.x = GetScreenWidth() - 50;
	RightPaddle.y = GetScreenHeight() / 2;
	RightPaddle.width = 10;
	RightPaddle.height = 100;
	RightPaddle.speed = 500;

	const char* WinnerText = nullptr;

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
			if (LeftPaddle.y - LeftPaddle.speed * GetFrameTime() > 0 + LeftPaddle.height/2)
			{
				LeftPaddle.y -= LeftPaddle.speed * GetFrameTime();
			}
			else
			{
				LeftPaddle.y = 0 + LeftPaddle.height / 2;
			}
		}
		if (IsKeyDown(KEY_S))
		{
			if (LeftPaddle.y + LeftPaddle.height + LeftPaddle.speed * GetFrameTime() < GetScreenHeight() + LeftPaddle.height/2)
			{
				LeftPaddle.y += LeftPaddle.speed * GetFrameTime();
			}
			else
			{
				LeftPaddle.y = GetScreenHeight() - LeftPaddle.height + LeftPaddle.height / 2;
			}
		}

		if (IsKeyDown(KEY_UP))
		{
			if (RightPaddle.y - RightPaddle.speed * GetFrameTime() > 0 + RightPaddle.height / 2)
			{
				RightPaddle.y -= RightPaddle.speed * GetFrameTime();
			}
			else
			{
				RightPaddle.y = 0 + RightPaddle.height / 2;
			}
		}
		if (IsKeyDown(KEY_DOWN))
		{
			if (RightPaddle.y + RightPaddle.height + RightPaddle.speed * GetFrameTime() < GetScreenHeight() + RightPaddle.height / 2)
			{
				RightPaddle.y += RightPaddle.speed * GetFrameTime();
			}
			else
			{
				RightPaddle.y = GetScreenHeight() - RightPaddle.height + RightPaddle.height / 2;
			}
		}


		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, RightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - RightPaddle.y) / (RightPaddle.height / 2) * - ball.speedX;
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, LeftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - LeftPaddle.y) / (LeftPaddle.height / 2) * ball.speedX;
			}
		}
		
		if (ball.x < 0)
		{
			WinnerText = "Right Player Wins!";
		}
		if (ball.x > GetScreenWidth())
		{
			WinnerText = "Left Player Wins!";
		}
		if (WinnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			WinnerText = nullptr;

		}

		BeginDrawing();
			ClearBackground(BLACK);	

			ball.Draw();
			LeftPaddle.Draw();
			RightPaddle.Draw();

			if (WinnerText)
			{
				int textWidth = MeasureText(WinnerText, 60);
				DrawText(WinnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}

			DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}