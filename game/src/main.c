#include "raylib.h"
int main(void)
{
	InitWindow(800, 450, "raylib [core] example - basic window");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Womp Womp", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}