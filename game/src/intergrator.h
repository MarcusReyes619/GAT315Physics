#include "body.h"

void ExplicitEuler(NcBody* body, float timestep) {

	body->pos = Vector2Add(body->pos, Vector2Scale(body->vel,timestep));
	body->vel = Vector2Add(body->vel, Vector2Scale(Vector2Scale(body->force , 1 / body->mass),timestep));
	

}