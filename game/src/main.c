#include "body.h"
#include "raylib.h"
#include "Math.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void)
{
	InitWindow(1280, 720, "Physic engine");
	SetTargetFPS(100);

	Body* bodies = (Body*)malloc(sizeof(Body) * MAX_BODIES);
	assert(bodies != NULL);
	int bodyCount = 0;

	//game
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 pos = GetMousePosition();
		if (IsMouseButtonPressed(0)) {

			bodies[bodyCount].pos = pos;
			bodies[bodyCount].vel = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
			bodyCount++;


		}


		//draw
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10,10,20,LIME);
		DrawText(TextFormat("FRAME: %.4f", dt),10,30,20,LIME);
		for (int i = 0; i < bodyCount; i++) {

			bodies[i].pos = Vector2Add(bodies[i].pos, bodies[i].vel);
			DrawCircle(bodies[i].pos.x, bodies[i].pos.y, 10, RED);

		}

		DrawCircle((int)pos.x, (int)pos.y, 10, YELLOW);


		EndDrawing();
	}
	CloseWindow();
	free(bodies);
	return 0;
}