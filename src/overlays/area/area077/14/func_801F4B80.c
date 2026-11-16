#include "area077_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4B80(void) {
    VECTOR   first;
    VECTOR   second;
    DVECTOR  screen;
    MATRIX   camera;
    LINE_F2* line;
    s32      noise;

    second.vx = g_Task->pos.x.fixed;
    first.vx  = second.vx;
    second.vy = g_Task->pos.y.fixed;
    first.vy  = second.vy;
    second.vz = g_Task->pos.z.fixed;
    first.vz  = second.vz;

    noise     = rand() & 0xFF;
    first.vx  = first.vx - 0x8000 + (noise << 8);
    noise     = rand() & 0xFF;
    first.vy  = first.vy - 0x8000 + (noise << 8);
    noise     = rand() & 0xFF;
    second.vx = second.vx - 0x8000 + (noise << 8);
    noise     = rand() & 0xFF;
    second.vy = second.vy - 0x8000 + (noise << 8);

    PushMatrix();
    Area_SetCameraMatrix(&camera);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    Area_ProjectPoint(&first.vx, &screen);
    line->x0 = screen.vx;
    line->y0 = screen.vy;
    Area_ProjectPoint(&second.vx, &screen);
    line->x1 = screen.vx;
    line->y1 = screen.vy;
    setRGB0(line, 0xC0, 0xC0, 0xC0);
    GFX_AddPrim(1, 0x10);
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F4B80);
#endif
