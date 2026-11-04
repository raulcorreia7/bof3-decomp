#include "battle_03.h"

MATCH void func_801E6C20(void) {
    volatile u16* gate;
    u8            count;
    u16           half;

    func_8014DAEC();
    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (count == 0u) {
        gate        = &g_BattleState;
        half        = (u16)(*gate | 0x20u);
        *(u16*)gate = half;
        func_801E5988();
    }
}
