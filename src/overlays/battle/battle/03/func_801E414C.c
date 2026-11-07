#include "battle_03.h"

MATCH void func_801E414C(void) {
    u16*          half;
    u16*          half2;
    u8            action_type;
    u32           flags;
    EnemyBattler* enemy;

    func_8014DAEC();
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0) {
        GFX_FreePaletteFadeTarget((void*)g_Task);
        half = &g_BattleState;
        *half &= ~BATTLE_STATE_REPRISAL_PENDING;
        FIELD(s8, g_Task, 0x01) = 6;
        FIELD(s8, g_Task, 0x02) = 4;
    } else {
        half2 = &g_BattleState;
        if ((*half2 & BATTLE_STATE_REPRISAL_PENDING) != 0) {
            *half2 = (*half2 & ~BATTLE_STATE_REPRISAL_PENDING) | BATTLE_STATE_REPRISAL_DONE;
        } else if ((g_BattleTargetSelector & BATTLE_TARGET_BOTH_SIDES) == 0) {
            action_type = *(u8*)&g_BattleActionType;
            if (action_type == BATTLE_ACTION_ATTACK) {
                if ((func_801E4368() & BYTE_MASK) != 0) {
                    *half2 |= BATTLE_STATE_REPRISAL_PENDING;
                }
            }
            action_type = *(u8*)&g_BattleActionType;
            if ((action_type == BATTLE_ACTION_ABILITY) &&
                ((FIELD(u16, &D_801CA71C, g_BattleActionId * 0x14) & 0x800) != 0) &&
                ((func_801E4368() & BYTE_MASK) != 0) &&
                ((FIELD(u8, &D_801CA718, g_BattleActionId * 0x14) & ABILITY_TARGET_ALL) == 0)) {
                g_BattleState |= BATTLE_STATE_REPRISAL_PENDING;
            }
        }
        Battle_ClearSlotPending(FIELD(u8, g_Task, 0x05));
        enemy = g_BattleCurrentEnemy;
        flags =
            enemy->turn.damage_flags.value & ~(COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED);
        enemy->turn.damage_flags.value = flags & ~0x200;
        FIELD(s8, g_Task, 0x01)        = 2;
        FIELD(s8, g_Task, 0x02)        = 0;
    }
    FIELD(s8, g_Task, 0x03) = 0;
}
