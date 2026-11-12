#include "boss018_16.h"

MATCH void func_800C29AC(s32 base, s32 pattern) {
    s32 row;
    s32 col;

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 2; col++) {
            MEM_PTR(u32, MAP_BUNDLE_BASE + 0x30)[(D_800C2DC4[base].row + row) * MEM(u8, MAP_BUNDLE_BASE) + (D_800C2DC4[base].column + col)] = D_800C2DC8[pattern];
        }
    }
}
