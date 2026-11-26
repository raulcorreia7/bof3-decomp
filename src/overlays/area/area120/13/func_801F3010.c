#include "area120_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3010(void) {
    s32             point[3];
    DVECTOR         screen;
    u8              scratch[32];
    u16*            pixels;
    AreaRiseTile*   tile;
    u8              row;
    u8              col;

    for (row = 0; row < 0x50; row++) {
        D_801F4F34[row] = 0;
    }
    Camera_SetMatrix(scratch);
    pixels   = MEM_PTR(u16, AREA_WORK);
    tile     = MEM_PTR(AreaRiseTile, AREA_WORK + 0x2D00u);
    point[0] = g_Actors[2].pos.x.fixed;
    point[1] = g_Actors[2].pos.y.fixed;
    point[2] = g_Actors[2].pos.z.fixed;
    Camera_ProjectPoint(point, &screen);
    D_801F4FD4 = 0;
    for (row = 0; row < (s16)AREA120_IMAGE_RECT->box.h; row++) {
        for (col = 0; col < (s16)AREA120_IMAGE_RECT->box.w; col++) {
            if (*pixels != 0) {
                tile->color = *pixels;
                tile->x     = (col + (screen.vx - AREA120_IMAGE_RECT->box.x)) << 4;
                tile->y     = (row + (screen.vy - AREA120_IMAGE_RECT->box.y)) << 4;
                if (D_801F4F34[col] < (s16)tile->y) {
                    D_801F4F34[col] = tile->y;
                }
                tile->timer = AREA120_IMAGE_RECT->box.h - row + (rand() & 7);
                tile->step  = rand() & 0x1F;
                tile->limit = col;
                tile++;
                D_801F4FD4++;
            }
            pixels++;
        }
    }
    TASK(Actor)->header.mode++;
}
#else
INCLUDE_ASM(func_801F3010);
#endif
