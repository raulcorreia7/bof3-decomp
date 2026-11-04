#include "battle_03.h"

MATCH void func_801E2024(void) {
    PartyBattler* work;
    u16*          gate;
    u8            count;
    u8            chance;

    work                      = g_SpadWork;
    count                     = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = count;
    if (count == 0) {
        if ((func_800A8F58() & BYTE_MASK) == 0) {
            chance = g_GameState->stats.critical_chance;
            if ((rand() % 100) < (s32)chance) {
                gate = &g_BattleState;
                *gate |= 0x80;
                func_801DD858(3);
            } else {
                func_801DD858(2);
            }
        } else {
            func_801DD858(3);
        }
        func_801DD858(4);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
