#include "area112_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2EA8(void) {
    AreaMapBundle* map;
    s32            flag;
    s32            x;
    s32            y;
    s32            n;
    s16            height;
    s32            value;

    flag = SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(TASK(Actor)->pos.x));
    n    = 0;
    if (COORD_INT(TASK(Actor)->pos.x) == 0) {
        for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
            for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
                (g_AreaCellCodes + y * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[x] = (TASK(Actor)->header.step != 2) ? 0x11 : 0;
            }
        }
    } else {
        for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
            map = (AreaMapBundle*)MAP_BUNDLE_BASE;
            for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
                MEM_PTR(u32, MAP_BUNDLE_BASE + 0x30u)[y * map->width + x] = D_801F4228[11 * flag + n] * 0x01010101;
                n++;
            }
        }
    }
    for (x = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x0; x < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].x_end; x++) {
        map = (AreaMapBundle*)MAP_BUNDLE_BASE;
        for (y = D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y0; y < D_801F4218[COORD_INT(TASK(Actor)->pos.x)].y_end; y++) {
            height = Area_HeightSample(x << 16, y << 16);
            value  = (-(COORD_INT(TASK(Actor)->pos.z) * 2) - height) / 32;
            /* FAKE: retail adds the bundle base after the offset; every u8* index or sum adds the base first. */
            *(u8*)(g_AreaMapBundle.height_offset * 4 + x + y * map->width + MAP_BUNDLE_BASE) = value;
        }
    }
}
#else
INCLUDE_ASM(func_801F2EA8);
#endif
