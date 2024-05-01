#include "body.h"
#include "raylib.h"
#include "Math.h"
#include "raymath.h"
#include "world.h"
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void)
{
	InitWindow(1280, 720, "Physic engine");
	SetTargetFPS(100);

	
	
	
	
	//game
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 pos = GetMousePosition();
		if (IsMouseButtonPressed(0)) {

			Body* body = CreateBody();
			body->pos = pos;
			body->vel = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(5, -5));


		}


		//draw
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10,10,20,LIME);
		DrawText(TextFormat("FRAME: %.4f", dt),10,30,20,LIME);

		Body* body = bodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			body->pos = Vector2Add(body->pos, body->vel);
			// draw body
			DrawCircle(body->pos.x, body->pos.y, 10, RED);

			body = body->next; // get next body
		}

		DrawCircle((int)pos.x, (int)pos.y, 10, YELLOW);


		EndDrawing();
	}
	CloseWindow();
	free(bodies);
	return 0;
}