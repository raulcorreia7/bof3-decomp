#include "area134_13.h"

MATCH void func_801F4E64(const s32* center, s32 radius) {
    u8  scratch[0x20];
    s32 i;
    s32 idx;

    Area_SetCameraMatrix(scratch);
    i = 0;
    do {
        idx = i & BYTE_MASK;
        func_801F4F0C(center, radius, (idx << 10), D_801F5848[idx], D_801F5858[idx]);
        i += 1;
    } while (((i & BYTE_MASK)) < 4u);
}
