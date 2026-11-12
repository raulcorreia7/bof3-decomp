#include "battle_03.h"

MATCH void func_801E414C(void) {
    u16*          half;
    u16*          half2;
    u8            action_type;
    u32           flags;
    EnemyBattler* enemy;

    Actor_StepAnimOnce();
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0) {
        GFX_FreePaletteFadeTarget((void*)g_Task);
        half = &g_Battle.state;
        *half &= ~BATTLE_STATE_REPRISAL_PENDING;
        g_Task->header.mode = 6;
        g_Task->header.step = 4;
    } else {
        half2 = &g_Battle.state;
        if ((*half2 & BATTLE_STATE_REPRISAL_PENDING) != 0) {
            *half2 = (*half2 & ~BATTLE_STATE_REPRISAL_PENDING) | BATTLE_STATE_REPRISAL_DONE;
        } else if ((g_Battle.target_selector & BATTLE_TARGET_BOTH_SIDES) == 0) {
            action_type = *(u8*)&g_Battle.action_type;
            if (action_type == BATTLE_ACTION_ATTACK) {
                if ((func_801E4368() & BYTE_MASK) != 0) {
                    *half2 |= BATTLE_STATE_REPRISAL_PENDING;
                }
            }
            action_type = *(u8*)&g_Battle.action_type;
            if ((action_type == BATTLE_ACTION_ABILITY) && ((FIELD(u16, &D_801CA71C, g_Battle.action_id * 0x14) & 0x800) != 0) && ((func_801E4368() & BYTE_MASK) != 0) &&
                ((FIELD(u8, &D_801CA718, g_Battle.action_id * 0x14) & ABILITY_TARGET_ALL) == 0)) {
                g_Battle.state |= BATTLE_STATE_REPRISAL_PENDING;
            }
        }
        Battle_ClearSlotPending(g_Task->slot);
        enemy                          = g_BattleCurrentEnemy;
        flags                          = enemy->turn.damage_flags.value & ~(COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED);
        enemy->turn.damage_flags.value = flags & ~0x200;
        g_Task->header.mode            = 2;
        g_Task->header.step            = 0;
    }
    g_Task->unk_03 = 0;
}
