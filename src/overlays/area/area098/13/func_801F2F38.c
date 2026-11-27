#include "area098_13.h"

MATCH void func_801F2F38(void) {
    s32       point[3];
    DVECTOR   screen;
    u8        scratch[32];
    u16*      pixels;
    TrailDot* dot;
    u8        row;
    u8        col;

    Camera_SetMatrix(scratch);
    point[0] = g_Game.members[SELF(Actor)->option_flags].pos.x.fixed;
    point[1] = g_Game.members[SELF(Actor)->option_flags].pos.y.fixed;
    point[2] = g_Game.members[SELF(Actor)->option_flags].pos.z.fixed;
    Camera_ProjectPoint(point, &screen);
    D_801F651C = 0;
    pixels     = MEM_PTR(u16, AREA_WORK);
    dot        = AREA_TRAIL_DOTS;
    for (row = 0; row < D_801F5F58[D_801F6520].h; row++) {
        for (col = 0; col < D_801F5F58[D_801F6520].w; col++) {
            if (*pixels != 0) {
                dot->color = *pixels;
                dot->x     = (screen.vx - D_801F5F58[D_801F6520].x) + col;
                dot->y     = (screen.vy - D_801F5F58[D_801F6520].y) + row;
                D_801F651C++;
                dot++;
            }
            pixels++;
        }
    }
    SELF(Actor)->header.mode++;
}
