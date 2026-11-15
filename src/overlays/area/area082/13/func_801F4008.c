#include "area082_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4008(void) {
    s32 i;
    s32 offset;

    D_1F800014[0].vz = 0x3A0;
    D_1F800014[1].vx = 0x400;
    D_1F800014[1].vy = 0;
    for (i = 0, offset = 0; i < 4; i++) {
        D_1F800014[0].vx = ((TO_COORD(D_801F5764[offset] * 3) + TO_COORD(75) + COORD_HALF) >> 9) - AREA_CELL_ORIGIN;
        D_1F800014[1].vz = (g_FrameCount << 5) + (i << 10);
        D_1F800014[0].vy = ((TO_COORD(D_801F5765[offset] * 3) + TO_COORD(86) + COORD_HALF) >> 9) - AREA_CELL_ORIGIN;
        func_801F46C8((g_Task->timer - 8) * 4, 0x1E, i << 10, 0x10);
        offset += 2;
    }
    func_801F4430();
    g_Task->timer++;
    if (g_Task->timer >= 0x10) {
        g_ScriptVars[0]++;
        g_Task->timer       = 0;
        g_Task->header.step = g_Task->header.step + 1;
    }
}
#else
INCLUDE_ASM(func_801F4008);
#endif
