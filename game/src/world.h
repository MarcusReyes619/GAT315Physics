#pragma once
#pragma once
#include "body.h"
#include "raylib.h"
//typedef struct NcBody Ncbody;

extern NcBody* ncBodies;
extern int ncBodyCount;
extern Vector2 ncGravity;

NcBody* CreateBody();

void DestoryBody(NcBody* body);
