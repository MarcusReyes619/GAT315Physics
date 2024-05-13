#pragma once
#pragma once
#include "raylib.h"
#include "body.h"
typedef struct NcBody Ncbody;

extern NcBody* ncBodies;
extern int ncBodyCount;
extern Vector2 ncGravity;


NcBody* CreateBody(Vector2 pos, float mass, NcBodyType bodyType);
void AddBody(NcBody* body);
void DestoryBody(NcBody* body);
void DestoryAllBody();

