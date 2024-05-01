#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum NcBodyTpye {
	STATIC,
	KINEMATIC,
	DYNIMIC

}NcBodyType;

typedef struct NcBody
{	
	NcBodyType body;

	Vector2 pos;
	Vector2 vel;
	Vector2 force;

	float mass;
	float inversMass; // 1 / mass (static = 0)

	struct NcBody* next;
	struct NcBody* prev;


}NcBody;

inline void ApplyForce(NcBody* body, Vector2 force) 
{
	body->force = Vector2Add(body->force, force);

}

inline ClearForce(NcBody* body) {

	body->force = Vector2Zero();
}

 
