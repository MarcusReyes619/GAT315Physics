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
    ncEditorData.GravatationValue = 2;
    ncEditorData.MassMinValue = 0.1f;
    ncEditorData.MassMaxValue = 1;

}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor()
{
    
    GuiGroupBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 688 }, "Editor");
    GuiSliderBar((Rectangle) { anchor01.x + 88, anchor01.y + 56, 120, 16 }, "MasMin", NULL, & MassMinValue, 0, 10);
    GuiSliderBar((Rectangle) { anchor01.x + 88, anchor01.y + 104, 120, 16 }, "MassMax", NULL, & MassMaxValue, 0, 10);
    GuiSliderBar((Rectangle) { anchor01.x + 88, anchor01.y + 152, 120, 16 }, "Gavatation", NULL, & GravatationValue, 0, 10);
}
