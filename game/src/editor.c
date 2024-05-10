#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
NcEditorData_t ncEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 830, 56 };

float MassMinValue = 0.0f;
float MassMaxValue = 0.0f;
float GravatationValue = 0.0f;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/jungle/style_jungle.rgs");
    ncEditorData.anchor01 = (Vector2){ 1032, 8 };
    ncEditorData.anchor02 = (Vector2){ 904, 64 };
    ncEditorData.anchor03 = (Vector2){ 896, 360 };

    ncEditorData.WindowBox000Active = true;
    ncEditorData.BodyTypeEditMode = false;
    ncEditorData.BodyTypeActive = 0;
    ncEditorData.MassMinValue = 0.0f;
    ncEditorData.MaxMassValue = 0.0f;
    ncEditorData.DampingValue = 0.0f;
    ncEditorData.GravityScaleValue = 0.0f;
    ncEditorData.GravitationValue = 0.0f;

}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor()
{
    if (ncEditorData.BodyTypeEditMode) GuiLock();

    if (ncEditorData.WindowBox000Active)
    {
        ncEditorData.WindowBox000Active = !GuiWindowBox((Rectangle) { ncEditorData.anchor02.x + 1, ncEditorData.anchor02.y + -12, 290, 723 }, "SAMPLE TEXT");
        GuiGroupBox((Rectangle) { ncEditorData.anchor02.x + 23, ncEditorData.anchor02.y + 35, 229, 285 }, "Body");
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 81, ncEditorData.anchor02.y + 79, 120, 16 }, "MassMIn", NULL, & ncEditorData.MassMinValue, 0, 100);
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 80, ncEditorData.anchor02.y + 109, 120, 16 }, "MaxMass", NULL, & ncEditorData.MaxMassValue, 0, 100);
        GuiGroupBox((Rectangle) { ncEditorData.anchor02.x + 11, ncEditorData.anchor02.y + 333, 260, 158 }, "World");
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 99, ncEditorData.anchor02.y + 361, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, 0, 100);
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 71, ncEditorData.anchor02.y + 181, 120, 16 }, "Gravity Scale", NULL, & ncEditorData.GravityScaleValue, 0, 100);
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 76, ncEditorData.anchor02.y + 145, 120, 16 }, "Damping", NULL, & ncEditorData.DampingValue, 0, 100);
        if (GuiDropdownBox((Rectangle) { ncEditorData.anchor02.x + 66, ncEditorData.anchor02.y + 45, 120, 24 }, "DYNAMIC;KINEMATIC;STATIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
    }

    GuiUnlock();
}
