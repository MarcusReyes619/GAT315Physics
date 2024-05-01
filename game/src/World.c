#pragma once
#include "world.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

NcBody* ncBodies = NULL;
int ncBodyCount = 0;

NcBody* CreateBody()
{
	/*
	Allocate memory for new Body
		Check if allocation is successful
		Initialize 'prev' to NULL and 'next' to the head of the list
		If list is not empty, update 'prev' of existing head
		Update head of the list to new Body
		Increment body count
		Return new Body
		*/

	NcBody* createdBody = (NcBody*)malloc(sizeof(NcBody));
	assert(createdBody);

	memset(createdBody, 0, sizeof(NcBody));
	
	createdBody->prev = NULL;
	createdBody->next = ncBodies;

	if (ncBodyCount != 0) {

		createdBody->prev = createdBody;
	}
	ncBodies = createdBody;
	ncBodyCount++;

	
	
	return createdBody;
}

void DestoryBody(NcBody* body)
{
	assert(body);
	/*
	Assert if provided Body is not NULL
		If 'prev' is not NULL, set 'prev->next' to 'body->next'
		If 'next' is not NULL, set 'next->prev' to 'body->prev'
		If body is the head, update head to 'body->next'
		Decrement body count
		Free the body
		*/

	if(body->prev != NULL) body->prev->next = body->next;
	if (body->next != NULL)body->next->prev = body->prev;

	if (body->prev == NULL) {
		body = body->next;
	}
	ncBodyCount--;
	free(body);




}
