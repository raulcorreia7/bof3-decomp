#include "area112_13.h"

/* Marks the gate span's cells with byte code 0x11 (0 while the task step is 2), writes the
 * span's cell words from the gate's shade row when the cell column is not zero, then rewrites
 * each cell's height byte from the ground height and the gate's z. */
MATCH void func_801F2EA8(void) {
    s32 n;
    s32 flag;
    s32 x;
    s32 y;
    s32 value;
    s32 shade;
    s16 height;

    n    = 0;
    flag = SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(TASK(Actor)->pos.x));
    if (COORD_INT(TASK(Actor)->pos.x) == 0) {
        for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
            for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
                *(g_AreaCellCodes + y * *(u8*)MAP_BUNDLE_BASE + x) = TASK(Actor)->header.step != 2 ? 0x11 : 0;
            }
        }
    } else {
        for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
            for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
                shade = D_801F4228[flag][n++];
                value = (shade << 24) | (shade << 16) | (shade << 8) | shade;
                ((AreaCellCorners*)((MAP_BUNDLE_BASE + 0x30) + (y * *(u8*)MAP_BUNDLE_BASE << 2) + (x << 2)))->word = value;
            }
        }
    }
    for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
        for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
            height                                                                              = Area_HeightSample(x << 16, y << 16);
            value = (-(COORD_INT(TASK(Actor)->pos.z) * 2) - height) / 32;
            *(u8*)(g_AreaMapHeightOffset * 4 + x + y * *(u8*)MAP_BUNDLE_BASE + MAP_BUNDLE_BASE) = value;
        }
    }
}
