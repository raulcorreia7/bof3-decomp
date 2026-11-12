#include "area132_13.h"

MATCH u8 func_801F38B0(void) {
    u8  scratch[32];
    u8* effect;
    u8  result;
    u8  index;

    Area_SetCameraMatrix(scratch);
    result     = 0;
    D_801F4A88 = MEM_PTR(u8, AREA_WORK);
    index      = 0;
    do {
        if (D_801F4A88[0] != 0u) {
            if (g_Task->header.mode == 0) {
                effect = D_801F4A88;
                FIELD(s32, effect, 0x4) += 8192;
                FIELD(u16, effect, 0x14) += 8;
                effect[3] -= 2;
            } else {
                FIELD(s32, D_801F4A88, 0x4) += 8192;
                FIELD(s32, D_801F4A88, 0x4) += rcos(D_801F4A88[0x17] << 8);
                FIELD(s32, D_801F4A88, 0xC) += rsin(D_801F4A88[0x17] << 8) << 8;
                D_801F4A88[3] -= 2;
            }
            if (--D_801F4A88[2] == 0) {
                D_801F4A88[0] = 0;
            }
            func_801F3560(D_801F4A88);
            result = 1;
        }
        index += 1;
        D_801F4A88 += 0x18;
    } while (index < 32u);
    return result;
}
