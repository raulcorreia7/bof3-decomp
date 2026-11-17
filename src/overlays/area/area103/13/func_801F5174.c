#include "area103_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5174(s32 steps, s32 radius) {
    s32 height;

    height                    = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    g_ScratchPadVectors[0].vz = -height / 2 + radius;
    g_ScratchPadVectors[1].vz = -height / 2 - radius;
    g_ScratchPadVectors[0].vx = steps;
}
#else
INCLUDE_ASM(func_801F5174);
#endif
