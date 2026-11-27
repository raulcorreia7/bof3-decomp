#include "battle_03.h"

MATCH void func_801E2024(void) {
    PartyMember* work;
    u16*         gate;
    u8           count;
    u8           chance;

    work         = SELF(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        if ((func_800A8F58() & BYTE_MASK) == 0) {
            chance = g_Game.current->chr.stats.critical_chance;
            if ((RANDOM_PERCENT()) < chance) {
                gate = &g_Battle.flags;
                *gate |= 0x80;
                Battle_PlayEffectSE(3);
            } else {
                Battle_PlayEffectSE(2);
            }
        } else {
            Battle_PlayEffectSE(3);
        }
        Battle_PlayEffectSE(4);
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
