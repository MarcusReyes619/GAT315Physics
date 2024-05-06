#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "intergrator.h"
#include "raymath.h"
#include "force.h"
#include "world.h"
#include <stdlib.h>
#include <assert.h>


int main(void)
{
	InitWindow(1280, 720, "Physic engine");
	SetTargetFPS(100);

	//initialzie world
	ncGravity = (Vector2){ 0,0 };
	
	
	//game
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		
		Vector2 pos = GetMousePosition();
		if (IsMouseButtonDown(0)) {

			NcBody* body = CreateBody();
			body->pos = pos;
			


			body->mass = GetRandomFloatValue(1, 10);
			body->inversMass = 1 / body->mass;
			body->type = BT_DYNIMIC;
			body->damping = 0.5f;
			body->graviryScale = 5;
			ApplyForce(body, (Vector2){GetRandomFloatValue(-60, 60), GetRandomFloatValue(-60,60) }, FM_VELOCITY);
		}

		//apply force
		NcBody* body = ncBodies;
		ApllyGravitation(ncBodies, 800);

		//while (body) // do while we have a valid pointer, will be NULL at the end of the list
		//{
		//	//ApplyForce(body, CreateVector2(0,-200), FM_FORCE);
		//	body = body->next;
		//}

		//apply force
		body = ncBodies;
		while (body) 
		{
			Step(body, dt);
			body = body->next;
		}

		//draw
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10,10,20,LIME);
		DrawText(TextFormat("FRAME: %.4f", dt),10,30,20,LIME);


		body = ncBodies;
		while (body) 
		{
			DrawCircle((int)body->pos.x, (int)body->pos.y, body->mass, RED);
			body = body->next;
		}

		DrawCircle((int)pos.x, (int)pos.y, 10, YELLOW);


		EndDrawing();
	}
	CloseWindow();
	free(ncBodies);
	return 0;
}