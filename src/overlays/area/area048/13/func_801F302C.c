#include "area048_13.h"

MATCH void func_801F302C(s32* first, s32* second, Actor* task) {
    LINE_F2* line;
    u16      size[2];
    u16      scale[2];
    MATRIX   camera;
    s32      angle;
    u16      angle1;
    u16      angle2;
    s16      radius1;
    s16      radius2;

    GFX_AddDitheredDrawMode(3, GetTPage(0, 1, 960, 0));
    Area_SetCameraMatrix(&camera);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    Area_ProjectPoint(first, (DVECTOR*)&line->x0);
    Area_ProjectPoint(second, (DVECTOR*)&line->x1);
    setRGB0(line, D_801F4D5C[g_Task->unk_06 * 3], D_801F4D5D[g_Task->unk_06 * 3], D_801F4D5E[g_Task->unk_06 * 3]);
    GFX_AddPrim(3, sizeof(LINE_F2));
    angle   = ratan2(line->y1 - line->y0, line->x1 - line->x0);
    size[0] = 64;
    size[1] = 0;
    Game_ProjectWorldPoint(first, size, scale);
    angle1  = angle + ANGLE_90;
    radius1 = scale[0] + (g_FrameCount & 1);
    func_801F3274(line->x0, line->y0, radius1, angle1);
    Game_ProjectWorldPoint(second, size, scale);
    angle2  = angle + ANGLE_270;
    radius2 = scale[0] + (g_FrameCount & 1);
    func_801F3274(line->x1, line->y1, radius2, angle2);
    func_801F3434(line->x0, line->y0, radius1, angle1, line->x1, line->y1, radius2, angle2);
}
