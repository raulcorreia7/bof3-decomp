#include "boss018_16.h"
#include "area/area.h"

MATCH void func_800C29AC(s32 base, s32 pattern) {
    s32 row;
    s32 col;

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 2; col++) {
            MEM_PTR(u32, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)[(D_800C2DC4[base].y + row) * AREA_MAP_BUNDLE->width + (D_800C2DC4[base].x + col)] = D_800C2DC8[pattern];
        }
    }
}
