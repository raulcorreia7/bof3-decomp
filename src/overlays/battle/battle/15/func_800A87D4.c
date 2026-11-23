#include "battle_15.h"

/* Copies the battle work record into a queued slot and arms the active actor. */
MATCH void func_800A87D4(void) {
    u8*              type;
    u8*              work;
    BattleWorkImage* slot;
    u32              index;

    index = Battle_AllocEffect(0, 18);
    if ((index & BYTE_MASK) != GAME_NONE) {
        slot                                            = &g_BattleEffects[index & BYTE_MASK];
        /* one struct copy (the 16-byte block-move loop), read through the non-volatile cell */
        *slot                                           = *(BattleWorkImage*)g_BattleWorkCell;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 0;
        g_BattleEffects[index & BYTE_MASK].step_index   = 0x12;
        g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_03       = 0;
        g_BattleEffects[index & BYTE_MASK].unk_04       = 0;
        g_BattleEffects[index & BYTE_MASK].header.flags = g_BattleEffects[index & BYTE_MASK].header.flags & 0xBF;
        work                                            = TASK_BYTES;
        g_BattleEffects[index & BYTE_MASK].target.bytes = work;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = work[0xB];
        work                                            = TASK_BYTES;
        if (work[0xB] != 0) {
            work[0xB]--;
        }
    }
    type = &g_Battle.target_selector;
    if (*type < 3) {
        Battle_MoveRangeToward((BattleRange*)&g_Game.members[*type], 0x50);
        if (func_800AF5FC((BattleRange*)&g_Game.members[*type], 0x10000) != 0) {
            Script_Select((TASK(PartyMember)->facing + 0x44) & BYTE_MASK);
            Battle_MarkDamaged(*type);
            TASK(PartyMember)->header.mode++;
        }
    } else {
        Battle_MoveRangeToward((BattleRange*)&((volatile EnemyBattler*)g_BattleEnemies)[*type], 0x50);
        if (func_800AF5FC((BattleRange*)&((volatile EnemyBattler*)g_BattleEnemies)[*type], 0x10000) != 0) {
            Script_Select((TASK(PartyMember)->facing + 0x44) & BYTE_MASK);
            Battle_MarkDamaged(*type);
            TASK(PartyMember)->header.mode++;
        }
    }
    func_801DEE4C();
}
