#include "battle_03.h"

MATCH void func_801E2024(void) {
    PartyMember* work;
    u16*         gate;
    u8           count;
    u8           chance;

    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        if ((func_800A8F58() & BYTE_MASK) == 0) {
            chance = g_Game.current->chr.stats.critical_chance;
            if ((RANDOM_PERCENT()) < chance) {
                gate = &g_Battle.state;
                *gate |= 0x80;
                Battle_PlayEffectCue(3);
            } else {
                Battle_PlayEffectCue(2);
            }
        } else {
            Battle_PlayEffectCue(3);
        }
        Battle_PlayEffectCue(4);
        g_Task->header.step = g_Task->header.step + 1;
    }
}
