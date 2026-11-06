#include "area134_13.h"

MATCH void func_801F4E64(const s32* center, s32 radius) {
    u8  scratch[0x20];
    s32 i;
    s32 index;

    Area_SetCameraMatrix(scratch);
    i = 0;
    do {
        index = i & BYTE_MASK;
        func_801F4F0C(center, radius, (index << 10), D_801F5848[index], D_801F5858[index]);
        i += 1;
    } while (((i & BYTE_MASK)) < 4u);
}
