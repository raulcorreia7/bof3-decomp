#include "battle_03.h"

MATCH void func_801E45DC(void) {
    PartyBattler* work;
    u32           slot;
    u8            count;

    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        if ((g_BattleCurrentEnemy->target_flags_FC & 0x10) != 0) {
            func_800AAC88(g_BattleCurrentEnemy->damage_F8, g_Task->slot);
        } else {
            slot                               = Battle_AllocEffect(0, 1) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].unk_07       = 3;
            g_BattleEffects[slot].unk_27       = 0;
        }
        g_Task->unk_03 = g_Task->unk_03 + 1;
    }
    g_Task->x.raw = g_Task->x.raw - g_Task->unk_0C;
    g_Task->y.raw = g_Task->y.raw - g_Task->unk_10;
    func_801E30F8();
}
