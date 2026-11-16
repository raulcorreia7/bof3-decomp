#include "area082_13.h"

MATCH void func_801F4F88(void) {
    setVector(&g_ScratchPadVectors[0], -0x2E40, -0x3240, -0x3E0);
    setVector(&g_ScratchPadVectors[1], 0, 0, g_FrameCount << 5);
    func_801F46C8(g_Task->timer * 4, 0x1F, 0, 0x18);
    D_8014933A = 0;
    func_801F5428(0x10001805);
    g_Task->timer++;
    if (g_Task->timer >= 8) {
        g_Task->header.step++;
    }
}
