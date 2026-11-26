#include "area168_13.h"

MATCH void func_801F2E10(s32* first, s32* second) {
    LINE_F2* line;
    u16      size[2];
    u16      scale[2];
    MATRIX   camera;
    s32      angle;
    u16      radius1;
    u16      radius2;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
    Area_CellAddPrim(SELF(Actor)->vx, SELF(Actor)->vy, 1, sizeof(DR_MODE));
    Camera_SetMatrix(&camera);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    Camera_ProjectPoint(first, (DVECTOR*)&line->x0);
    Camera_ProjectPoint(second, (DVECTOR*)&line->x1);
    setRGB0(line, D_801F4B2C[SELF(Actor)->unk_06 * 3], D_801F4B2D[SELF(Actor)->unk_06 * 3], D_801F4B2E[SELF(Actor)->unk_06 * 3]);
    Area_CellAddPrim(SELF(Actor)->vx, SELF(Actor)->vy, 1, sizeof(LINE_F2));
    angle   = ratan2(line->y1 - line->y0, line->x1 - line->x0);
    size[0] = 64;
    size[1] = 0;
    Game_ProjectWorldPoint(first, size, scale);
    radius1 = scale[0] + (g_FrameCount & 1);
    Game_ProjectWorldPoint(second, size, scale);
    radius2 = scale[0] + (g_FrameCount & 1);
    func_801F3040(line->x0, line->y0, radius1, angle + ANGLE_90, line->x1, line->y1, radius2, angle + ANGLE_270);
}
