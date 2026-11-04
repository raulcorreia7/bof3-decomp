#include "battle_03.h"

MATCH void func_801E45DC(void) {
    PartyBattler* work;
    u32           slot;
    u8            count;

    work                      = g_SpadWork;
    count                     = work->word_08.byte.unk_0A - 1;
    work->word_08.byte.unk_0A = count;
    if (count == 0) {
        if ((g_BattleCurrentEnemy->target_flags_FC & 0x10) != 0) {
            func_800AAC88(g_BattleCurrentEnemy->damage_F8, g_SpadWork->slot);
        } else {
            slot                                = Battle_AllocEffect(0, 1) & BYTE_MASK;
            g_BattleEffects[slot].work_74.party = g_SpadWork;
            g_BattleEffects[slot].unk_07        = 3;
            g_BattleEffects[slot].unk_27        = 0;
        }
        g_SpadWork->unk_03 = g_SpadWork->unk_03 + 1;
    }
    g_SpadWork->coord_x_34.raw = g_SpadWork->coord_x_34.raw - g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw = g_SpadWork->coord_y_38.raw - g_SpadWork->unk_10;
    func_801E30F8();
}
