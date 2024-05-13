#pragma once
#include "world.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

NcBody* ncBodies = NULL;
int ncBodyCount = 0;
Vector2 ncGravity;

NcBody* CreateBody(Vector2 pos, float mass, NcBodyType bodyType)
{
	
	NcBody* createdBody = (NcBody*)malloc(sizeof(NcBody));
	assert(createdBody);

	memset(createdBody, 0, sizeof(NcBody));
	createdBody->pos = pos;
	createdBody->mass = mass;
	createdBody->inversMass = (bodyType == BT_DYNIMIC) ? 1 / mass : 0;
	createdBody->type = bodyType;

	return createdBody;
}


void AddBody(NcBody* body) {

	assert(body);

	body->prev = NULL;
	body->next = ncBodies;

	if (ncBodies) ncBodies->prev = body;
	//set head of elements to new element
	ncBodies = body;
	ncBodyCount++;
}

void DestoryBody(NcBody* body)
{
	assert(body);

	if(body->prev != NULL) body->prev->next = body->next;
	if (body->next != NULL)body->next->prev = body->prev;

	if (body->prev == NULL) {
		body = body->next;
	}
	ncBodyCount--;
	free(body);

}

void DestoryAllBody() {

}
