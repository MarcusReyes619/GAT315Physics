#pragma once
#include "raylib.h"

typedef struct NcEditorData {

	float MassMinValue;
	float MassMaxValue;
	float GravatationValue;

}NcEditorData_t;

extern NcEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();