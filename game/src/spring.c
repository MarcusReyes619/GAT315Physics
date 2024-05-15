#include "spring.h"
#include "world.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


ncSpring_t* ncSprings;
int ncSpringCount = 0;
Vector2 ncGravity;

ncSpring_t* CreateSpring(NcBody* body1, NcBody* body2, float restLength, float k)
{

	ncSpring_t* spring = (ncSpring_t*)malloc(sizeof(NcBody));
	assert(spring);

	memset(spring, 0, sizeof(ncSpring_t));
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;

	return spring;
}


void AddSpring(ncSpring_t* spring) {

	assert(spring);
	spring->next = ncSprings;
	spring->prev = NULL;
	

	if (ncSprings) ncSprings->prev = spring;
	//set head of elements to new element
	ncSprings = spring;
	ncBodyCount++;
}

void DestorySpring(ncSpring_t* spring)
{
	assert(spring);

	if (spring->prev != NULL) spring->prev->next = spring->next;
	if (spring->next != NULL)spring->next->prev = spring->prev;

	if (spring->prev == NULL) {
		spring = spring->next;
	}
	ncBodyCount--;
	free(spring);

}

void DestoryAllSprings() {

}

void ApplySpringForce(ncSpring_t* spring) {
	for (ncSpring_t* spring = ncSprings; spring; spring = spring->next)
		{
			//Vector2 direction = <get direction vector from body2 to body1>
		Vector2 dir = Vector2Subtract(spring->body1->pos, spring->body2->pos);
		if (dir.x == 0 && dir.y == 0) continue;

		float length = Vector2Length(dir);
		float x = length - spring->restLength;
		float force = -spring->k * x;

		Vector2 ndirection = Vector2Normalize(dir);

			
		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(ndirection, -force), FM_FORCE);
		}
	
}

