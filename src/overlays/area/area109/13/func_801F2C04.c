#include "area109_13.h"

MATCH void func_801F2C04(void) {
    u8  step;
    u16 height;
    s32 shade;
    s32 row;
    s32 col;

    step = SELF(Actor)->header.step;
    if (step != func_801F2D04()) {
        SELF(Actor)->header.step      = func_801F2D04();
        height                        = g_AreaVariantHeights[SELF(Actor)->header.step];
        COORD_INT(SELF(Actor)->pos.z) = height;
        shade                         = ((s16)height != -0x80) << 4;
        for (row = 3; row < 7; row++) {
            for (col = 0x42; col < 0x45; col++) {
                *(g_AreaCellCodes + row * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width + col) = shade;
            }
        }
    }
    g_AreaSceneMode = g_AreaVariantModes[SELF(Actor)->header.step];
}
