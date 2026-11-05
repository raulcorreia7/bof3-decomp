#include "area108_14.h"

MATCH s32 func_801F3034(void) {
    u8  scratch[0x20];
    u8  i;
    s32 result;

    Area_SetCameraMatrix(scratch);

    result     = 0;
    D_801F63EC = MEM_PTR(u8, 0x800E4800u);
    i          = 0u;

    do {
        if (D_801F63EC[0] != 0u) {
            D_801F56F4[D_801F63EC[1]]();
            func_801F2D40(D_801F63EC);
            result = 1;
        }

        D_801F63EC += 0x28;
        i += 1u;
    } while (i < 16u);

    return result;
}
