#include "battle_15.h"

MATCH void func_800A2598(void) {
    s16* record;
    s32  slot;
    u8   mode;

    mode = LOBU(g_BattleTarget);
    if (mode < 3u) {
        g_BattleTargetRecord[2] = Battle_CalcDamage(g_BattleActiveBattler, mode, 0xFFFF);
    } else {
        g_BattleTargetRecord[2] = Battle_CalcDamage(g_BattleActiveBattler, mode, 0xFFFF);
        slot                    = LOBU(g_BattleTarget);
        slot -= 3;
        if (D_801EB630[slot].unk_7D == 4) {
            record = *(s16**)&g_BattleTargetRecord;
            record[2] *= 2;
        }
    }
}
