#pragma once
#pragma once
#include "body.h"
#include "raylib.h"
//typedef struct NcBody Ncbody;

extern NcBody* ncBodies;
extern int ncBodyCount;
extern Vector2 ncGravity;

void AddBody(NcBody* body);
NcBody* CreateBody(Vector2 pos, float mass, NcBodyType bodyType);

void DestoryBody(NcBody* body);
