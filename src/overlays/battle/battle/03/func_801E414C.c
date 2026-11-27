#include "battle_03.h"

MATCH void func_801E414C(void) {
    u16*          half;
    u16*          half2;
    u8            action_type;
    u32           flags;
    EnemyBattler* enemy;

    Script_AnimStepOnce();
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0) {
        GFX_PaletteFreeFadeTarget(SELF(void));
        half = &g_Battle.flags;
        *half &= ~BATTLE_STATE_REPRISAL_PENDING;
        SELF(PartyMember)->header.mode = 6;
        SELF(PartyMember)->header.step = 4;
    } else {
        half2 = &g_Battle.flags;
        if ((*half2 & BATTLE_STATE_REPRISAL_PENDING) != 0) {
            *half2 = (*half2 & ~BATTLE_STATE_REPRISAL_PENDING) | BATTLE_STATE_REPRISAL_DONE;
        } else if ((g_Battle.target_selector & BATTLE_TARGET_BOTH_SIDES) == 0) {
            action_type = g_Battle.action_type;
            if (action_type == BATTLE_ACTION_ATTACK) {
                if ((func_801E4368() & BYTE_MASK) != 0) {
                    *half2 |= BATTLE_STATE_REPRISAL_PENDING;
                }
            }
            action_type = g_Battle.action_type;
            if ((action_type == BATTLE_ACTION_ABILITY) && ((FIELD(u16, &D_801CA71C, g_Battle.action_id * 0x14) & 0x800) != 0) && ((func_801E4368() & BYTE_MASK) != 0) &&
                ((g_Abilities[g_Battle.action_id].targeting_flags & ABILITY_TARGET_FLAG_ALL) == 0)) {
                g_Battle.flags |= BATTLE_STATE_REPRISAL_PENDING;
            }
        }
        Battle_ClearSlotPending(SELF(PartyMember)->slot);
        enemy                          = g_BattleCurrentEnemy;
        flags                          = enemy->turn.damage_flags.value & ~(BATTLER_DAMAGE_UNK_4 | BATTLER_DAMAGE_UNK_5 | BATTLER_DAMAGE_TAKEN);
        enemy->turn.damage_flags.value = flags & ~0x200;
        SELF(PartyMember)->header.mode = 2;
        SELF(PartyMember)->header.step = 0;
    }
    SELF(PartyMember)->unk_03 = 0;
}
