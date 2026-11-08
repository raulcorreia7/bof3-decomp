#include "boss034_16.h"

MATCH void func_800C20A8(void) {
    s8* ending;

    if (g_Battle.outcome.result & 2) {
        BOSS_SEND_PARTY_TO_ENDING_POSE(0)
        BOSS_SEND_PARTY_TO_ENDING_POSE(1)
        BOSS_SEND_PARTY_TO_ENDING_POSE(2)
        if (!(g_Battle.boss_flags & 2)) {
            Char_AddAbility(0x40, 4, 0, 0);
            Char_AddAbility(0x40, D_800C2778, 0, 1);
        }
        g_BattleResult |= 8;
        func_801DDED8();
        ending = &D_80146875;
        *ending += 1;
        return;
    }
    func_801DDF00();
}
