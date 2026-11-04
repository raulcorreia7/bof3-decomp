#include "area082_13.h"

MATCH void func_801F4F88(void) {
    D_1F800014[0].vx = -0x2E40;
    D_1F800014[0].vy = -0x3240;
    D_1F800014[0].vz = -0x3E0;
    D_1F800014[1].vx = 0;
    D_1F800014[1].vy = 0;
    D_1F800014[1].vz = g_FrameCount << 5;
    func_801F46C8(g_SpadWork->unk_09 * 4, 0x1F, 0, 0x18);
    D_8014933A = 0;
    func_801F5428(0x10001805);
    g_SpadWork->unk_09++;
    if (g_SpadWork->unk_09 >= 8) {
        g_SpadWork->state_02++;
    }
}
