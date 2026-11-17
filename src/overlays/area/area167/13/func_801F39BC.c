#include "area167_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F39BC(void) {
    s32 shade;

    shade = g_Task->param.unk_0B - 0x4B;
    if (g_Task->header.step == 0) {
        g_ScratchPadVectors[0].vx = shade;
    }
}
#else
INCLUDE_ASM(func_801F39BC);
#endif
