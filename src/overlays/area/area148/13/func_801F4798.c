#include "area148_13.h"

MATCH void func_801F4798(void* first, void* second) {
    LINE_F2* line;
    u16      size[2];
    u16      scale[2];
    s32      angle;
    u16      radius1;
    u16      radius2;
    /* FAKE: the call to Camera_SetMatrix takes no argument here, and no local explains 0x30 bytes of frame. */
    FAKE_STACK_PADS(u8, 0x30);

    if (g_AreaDrawFlags != 0 && SYS_TestFlag(g_SceneEventFlags, 0x6A) != 0) {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(SELF(Actor)->unk_18, SELF(Actor)->unk_1C, 0, sizeof(DR_MODE));
        ((void (*)(void))Camera_SetMatrix)();
        line = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(line);
        SetSemiTrans(line, 0);
        Camera_ProjectPoint(first, (DVECTOR*)&line->x0);
        Camera_ProjectPoint(second, (DVECTOR*)&line->x1);
        setRGB0(line, D_801F6138[SELF(Actor)->unk_06][0], D_801F6138[SELF(Actor)->unk_06][1], D_801F6138[SELF(Actor)->unk_06][2]);
        Area_CellAddPrim(SELF(Actor)->unk_18, SELF(Actor)->unk_1C, 0, sizeof(LINE_F2));
        angle   = ratan2(line->y1 - line->y0, line->x1 - line->x0);
        size[0] = 64;
        size[1] = 0;
        Game_ProjectWorldPoint(first, size, scale);
        radius1 = scale[0] + (g_FrameCount & 1);
        Game_ProjectWorldPoint(second, size, scale);
        radius2 = scale[0] + (g_FrameCount & 1);
        func_801F4DF0(line->x1, line->y1, radius2, angle + ANGLE_270);
        func_801F4A50(line->x0, line->y0, radius1, angle + ANGLE_90, line->x1, line->y1, radius2, angle + ANGLE_270);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(SELF(Actor)->unk_18, SELF(Actor)->unk_1C, 0, sizeof(DR_MODE));
    }
}
