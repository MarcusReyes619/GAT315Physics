#pragma once
#include "raylib.h"

typedef struct NcEditorData {

    Vector2 anchor01;
    Vector2 anchor02;
    Vector2 anchor03;

    bool WindowBox000Active;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float MassMinValue;
    float MaxMassValue;
    float DampingValue;
    float  GravityScaleValue;
    float GravitationValue;
    //------------------------------

}NcEditorData_t;

extern NcEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 pos);
void DrawEditor(Vector2 pos);

struct NcBody* GetBodyIntersect(struct NcBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct NcBody* body, Vector2 position);