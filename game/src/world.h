#pragma once
#pragma once
#include "body.h"

extern NcBody* ncBodies;
extern int ncBodyCount;

NcBody* CreateBody();

void DestoryBody(NcBody* body);
