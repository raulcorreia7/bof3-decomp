#include "battle_03.h"

MATCH void func_801E6C20(void) {
    volatile u16* gate;
    u8            count;
    u16           half;

    Actor_StepAnimOnce();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0u) {
        gate        = &g_Battle.state;
        half        = (*gate | 0x20u);
        *(u16*)gate = half;
        Effect_Reset();
    }
}
