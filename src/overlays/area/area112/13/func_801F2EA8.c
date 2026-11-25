#include "area112_13.h"

#ifdef NON_MATCHING
/* Marks the gate span's cells with byte code 0x11 (0 while the task step is 2), writes the
 * span's cell words from the gate's shade row when the cell column is not zero, then rewrites
 * each cell's height byte from the ground height and the gate's z. */
NON_MATCHING void func_801F2EA8(void) {
    s32 n;
    s32 flag;
    s32 x;
    s32 y;
    s32 value;
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
                value                                     = D_801F4228[flag * 11 + n++];
                D_80104030[x + y * *(u8*)MAP_BUNDLE_BASE] = (value << 24) | (value << 16) | (value << 8) | value;
            }
        }
    }
    for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
        for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
            height                                                                              = Area_HeightSample(x << 16, y << 16);
            value                                                                               = (-(COORD_INT(TASK(Actor)->pos.z) * 2) - height) / 32;
            *(u8*)(g_AreaMapHeightOffset * 4 + x + y * *(u8*)MAP_BUNDLE_BASE + MAP_BUNDLE_BASE) = value;
        }
    }
}
#else
INCLUDE_ASM(func_801F2EA8);
#endif
