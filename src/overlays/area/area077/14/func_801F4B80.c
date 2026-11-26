#include "area077_14.h"

MATCH void func_801F4B80(void) {
    VECTOR   first;
    VECTOR   second;
    DVECTOR  screen;
    MATRIX   camera;
    LINE_F2* line;

    second.vx = SELF(Actor)->pos.x.fixed;
    first.vx  = second.vx;
    second.vy = SELF(Actor)->pos.y.fixed;
    first.vy  = second.vy;
    second.vz = SELF(Actor)->pos.z.fixed;
    first.vz  = second.vz;

    first.vx += ((rand() & 0xFF) << 8) - 0x8000;
    first.vy += ((rand() & 0xFF) << 8) - 0x8000;
    second.vx += ((rand() & 0xFF) << 8) - 0x8000;
    second.vy += ((rand() & 0xFF) << 8) - 0x8000;

    PushMatrix();
    Camera_SetMatrix(&camera);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    Camera_ProjectPoint(&first.vx, &screen);
    setXY0(line, screen.vx, screen.vy);
    Camera_ProjectPoint(&second.vx, &screen);
    line->x1 = screen.vx;
    line->y1 = screen.vy;
    line->r0 = line->g0 = line->b0 = 0xC0;
    GFX_AddPrim(GFX_LAYER_UI, 0x10);
    PopMatrix();
}
