#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum NcBodyTpye 
{
	BT_DYNIMIC,
	BT_KINEMATIC,
	BT_STATIC
	
	

}NcBodyType;

typedef enum {
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY

}ncForceMode;

typedef struct NcBody
{	
	NcBodyType type;

	//acceleration->vel->pos
	Vector2 pos;
	Vector2 vel;
	Vector2 accleration;
	Vector2 force;

	float mass;
	float inversMass; // 1 / mass (static = 0)
	float graviryScale;
	float damping;
	float restitution;
	Color color;

	struct NcBody* next;
	struct NcBody* prev;


}NcBody;

inline void ApplyForce(NcBody* body, Vector2 force, ncForceMode forceMode) 
{
	if (body->type != BT_DYNIMIC) return;

	
	switch (forceMode) {
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		//applys a sudden change in momentum
		body->vel = Vector2Scale(force, body->inversMass);
		break;
	case FM_VELOCITY:
		body->vel = force;
		break;


	}

}

inline ClearForce(NcBody* body) {

	body->force = Vector2Zero();
}

void Step(NcBody* body, float timestep);
 

