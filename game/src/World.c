#pragma once
#include "world.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

NcBody* ncBodies = NULL;
int ncBodyCount = 0;
Vector2 ncGravity;

NcBody* CreateBody()
{
	
	NcBody* createdBody = (NcBody*)malloc(sizeof(NcBody));
	assert(createdBody);

	memset(createdBody, 0, sizeof(NcBody));
	
	createdBody->prev = NULL;
	createdBody->next = ncBodies;

	if (ncBodyCount != 0) 
	{

		createdBody->prev = createdBody;
	}
	ncBodies = createdBody;
	ncBodyCount++;

	
	
	return createdBody;
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

