#include "area086_13.h"

/* Marks the gate span's cells with byte code 0x21 (0 while pos.z is -0x200), then rewrites each cell's height byte from the ground height and pos.z. */
MATCH void func_801F2DE8(void) {
    AreaMapBundle* map;
    s32            x;
    s32            y;
    s16            height;
    s32            value;

    value = COORD_INT(SELF(Actor)->pos.z) != -0x200 ? 0x21 : 0;
    for (x = D_801F364C[COORD_INT(SELF(Actor)->pos.x)].x0; x < D_801F364C[COORD_INT(SELF(Actor)->pos.x)].x_end; x++) {
        for (y = D_801F364C[COORD_INT(SELF(Actor)->pos.x)].y0; y < D_801F364C[COORD_INT(SELF(Actor)->pos.x)].y_end; y++) {
            (g_AreaCellCodes + y * AREA_MAP_BUNDLE->width)[x] = value;
        }
    }
    for (x = D_801F364C[COORD_INT(SELF(Actor)->pos.x)].x0; x < D_801F364C[COORD_INT(SELF(Actor)->pos.x)].x_end; x++) {
        map = AREA_MAP_BUNDLE;
        for (y = D_801F364C[COORD_INT(SELF(Actor)->pos.x)].y0; y < D_801F364C[COORD_INT(SELF(Actor)->pos.x)].y_end; y++) {
            height                                                                           = Area_HeightSample(x << 16, y << 16);
            value                                                                            = (-(COORD_INT(SELF(Actor)->pos.z) * 2) - height) / 32;
            /* FAKE: retail adds the bundle base after the offset; every u8* index or sum adds the base first. */
            *(u8*)(g_AreaMapBundle.height_offset * 4 + x + y * map->width + MAP_BUNDLE_BASE) = value;
        }
    }
}
