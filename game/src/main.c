#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "intergrator.h"
#include "raymath.h"
#include "force.h"
#include "world.h"
#include "render.h"
#include "editor.h"
#include <stdlib.h>
#include <assert.h>


int main(void)
{
	InitWindow(1280, 720, "Physic engine");
	InitEditor();
	SetTargetFPS(100);

	//initialzie world
	ncScreenZoom = 5;
	ncGravity = (Vector2){ 0,-1 };
	
	
	//game
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		
		Vector2 pos = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);
		UpdateEditor(pos);

#pragma region InputControlles

		if (IsMouseButtonDown(0)) {

			NcBody* body = CreateBody();
			body->pos = ConvertScreenToWorld(pos);
			body->mass = GetRandomFloatValue(ncEditorData.MassMinValue,ncEditorData.MassMaxValue);
			body->inversMass = 1 / body->mass;
			body->type = BT_DYNIMIC;
			body->damping = 0.5f;
			body->graviryScale = 5;
			body->color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
			//ApplyForce(body, (Vector2){GetRandomFloatValue(-60, 60), GetRandomFloatValue(-60,60) }, FM_VELOCITY);
		}
		if (IsMouseButtonPressed(1)) {
			
			for (int i = 0; i <= 10; i++) {
				Vector2 force = Vector2Scale(GetVector2FromAnge(GetRandomFloatValue(0,360) * DEG2RAD), GetRandomFloatValue(1000,2000));
				NcBody* body = CreateBody();
				body->pos = pos;
				body->mass = 10;
				body->inversMass = 1 / body->mass;
				body->type = BT_DYNIMIC;
				body->damping = 0.5f;
				body->graviryScale = 5;
				body->color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
				
				ApplyForce(body, force, FM_IMPULSE);
			
			}
		}
	
		if (IsMouseButtonPressed(2)) {

			for (int i = 0; i <= 10; i++) {
				Vector2 force = Vector2Scale(GetVector2FromAnge(GetRandomFloatValue(0, 360) * DEG2RAD), GetRandomFloatValue(1000, 2000));
				NcBody* body = CreateBody();
				body->pos = pos;
				body->mass = 10;
				body->inversMass = 1 / body->mass;
				body->type = BT_DYNIMIC;
				body->damping = 0.5f;
				body->graviryScale = 5;
				body->color = ColorFromHSV(GetRandomFloatValue(180, 265), 1, 1);

				ApplyForce(body, force, FM_IMPULSE);

			}
		}
		if (IsMouseButtonPressed(3)) {

			for (int i = 0; i <= 10; i++) {
				Vector2 force = Vector2Scale(GetVector2FromAnge(GetRandomFloatValue(0, 360) * DEG2RAD), GetRandomFloatValue(1000, 2000));
				NcBody* body = CreateBody();
				body->pos = pos;
				body->mass = 10;
				body->inversMass = 1 / body->mass;
				body->type = BT_DYNIMIC;
				body->damping = 0.5f;
				body->graviryScale = 5;
				body->color = ColorFromHSV(GetRandomFloatValue(300, 360), 1, 1);

				ApplyForce(body, force, FM_IMPULSE);

			}
		}
#pragma endregion
		//apply force
		
		ApllyGravitation(ncBodies, ncEditorData.GravatationValue);

		for (NcBody* body = ncBodies; body; body = body->next) {
			Step(body, dt);
				
		}
		//draw
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps),10,10,20,LIME);
		DrawText(TextFormat("FRAME: %.4f", dt),10,30,20,LIME);


		//draw bods
	
		for (NcBody* body = ncBodies; body; body = body->next) {
				Vector2 screen = ConvertWorldToScreen(body->pos);
				DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), body->color);
		}

		DrawCircle((int)pos.x, (int)pos.y, 10, YELLOW);
		DrawEditor();

		EndDrawing();
	}
	CloseWindow();
	free(ncBodies);
	return 0;
}