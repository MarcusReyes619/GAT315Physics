#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "intergrator.h"
#include "raymath.h"
#include "force.h"
#include "spring.h"
#include "world.h"
#include "collision.h"
#include "contact.h"
#include "render.h"
#include "editor.h"
#include <stdlib.h>
#include <assert.h>


int main(void)
{
	NcBody* selecetedBody = NULL;
	NcBody* connectBody = NULL;

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
		
		//setting screen
		Vector2 pos = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);
		UpdateEditor(pos);
		
		selecetedBody = GetBodyIntersect(ncBodies, pos);

		if (selecetedBody) {
			Vector2 screen = ConvertScreenToWorld(selecetedBody->pos);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selecetedBody->mass) * 5, YELLOW);
		}
		
#pragma region InputControlles
		
		if (IsMouseButtonPressed(0)|| IsMouseButtonDown(0) && IsKeyDown(KEY_LEFT_SHIFT)) {

			NcBody* body = CreateBody(ConvertScreenToWorld(pos),ncEditorData.MassMinValue, ncEditorData.BodyTypeActive);		
			body->damping = ncEditorData.DampingValue;
			body->graviryScale = ncEditorData.GravityScaleValue;
			body->color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
			body->restitution = 0.3f;
			AddBody(body);
		}
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selecetedBody) connectBody = selecetedBody;
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) DrawLineBodyToPosition(connectBody,pos);
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) {

			if (selecetedBody && selecetedBody != connectBody) {

				ncSpring_t* spring = CreateSpring(connectBody, selecetedBody, Vector2Distance(connectBody->pos,selecetedBody->pos),20);
				AddSpring(spring);
			}
		}
			
			
#pragma endregion
		//apply force
		
		ApllyGravitation(ncBodies, ncEditorData.GravitationValue);
		ApplySpringForce(ncSprings);

	
		

		for (NcBody* body = ncBodies; body; body = body->next) {
			Step(body, dt);
				
		}

		//collision
		ncContact_t* contacts = NULL;
		CreateContacts(ncBodies, &contacts);
		SeparateContacts(contacts);
		ResolveContacts(contacts);

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

		//draw spring

		for (ncSpring_t* spring = ncSprings; spring; spring = spring->next) {

			Vector2 screen = ConvertWorldToScreen(spring->body1->pos);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->pos);
			DrawLine((int)screen.x, (int)screen.y, (int)screen2.x, (int)screen2.y, YELLOW);
			
		}

		//draw contacts
		for (ncContact_t* contact = contacts; contact; contact = contact->next) {

			Vector2 screen = ConvertWorldToScreen(contact->body1->pos);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.9f), RED);
		}


		DrawCircleLines((int)pos.x, (int)pos.y, 10, WHITE);
		DrawEditor(pos);

		EndDrawing();
	}

	DestoryAllSprings();
	DestoryAllBody();
	CloseWindow();
	
	return 0;
}