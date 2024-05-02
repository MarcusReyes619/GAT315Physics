#include "body.h"
#include "intergrator.h"
#include "world.h"

void Step(NcBody* body, float timestep) {

	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(ncGravity,body->graviryScale),body->mass));
	body->accleration = Vector2Scale(body->force, body->inversMass);
	ExplicitEuler(body, timestep);

	//apply damping
	float damping = 1 / (1 + (body->damping * timestep));
	body->vel = Vector2Scale(body->vel,damping);
	ClearForce(body);

}