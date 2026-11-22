#include "area082_13.h"

MATCH void func_801F4F88(void) {
    setVector(&g_ScratchPadVectors[0], -0x2E40, -0x3240, -0x3E0);
    setVector(&g_ScratchPadVectors[1], 0, 0, g_FrameCount << 5);
    func_801F46C8(TASK(Actor)->timer * 4, 0x1F, 0, 0x18);
    D_8014933A = 0;
    Area_DrawGradient(0x10001805);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 8) {
        TASK(Actor)->header.step++;
    }
}
