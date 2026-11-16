#include "area145_14.h"

MATCH void func_801F332C(s32* first, s32* second) {
    SVECTOR screen[2];
    u16     size[2];
    u16     scale[2];
    MATRIX  matrix;
    s32     angle;
    u16     angle1;
    u16     angle2;
    s16     radius1;
    s16     radius2;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Area_SetCameraMatrix(&matrix);
    /* Each point keeps a full SVECTOR: the projection fills the SDK's two-word result. */
    Area_ProjectPoint(first, (DVECTOR*)&screen[0]);
    Area_ProjectPoint(second, (DVECTOR*)&screen[1]);
    angle   = ratan2(screen[1].vy - screen[0].vy, screen[1].vx - screen[0].vx);
    size[0] = 0x10;
    size[1] = 0;
    Game_ProjectWorldPoint(first, size, scale);
    angle1  = angle + ANGLE_90;
    radius1 = scale[0] + (g_FrameCount & 1);
    func_801F34C8(screen[0].vx, screen[0].vy, radius1, angle1);
    Game_ProjectWorldPoint(second, size, scale);
    radius2 = scale[0] + (g_FrameCount & 1);
    angle2  = angle + ANGLE_270;
    func_801F34C8(screen[1].vx, screen[1].vy, radius2, angle2);
    func_801F3618(screen[0].vx, screen[0].vy, radius1, angle1, screen[1].vx, screen[1].vy, radius2, angle2);
}
