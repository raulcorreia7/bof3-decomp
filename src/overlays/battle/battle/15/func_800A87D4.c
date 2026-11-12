#include "battle_15.h"

/* The 0x74 bytes of the work record that a queued slot copies. */
typedef struct BattleWorkImage {
    u32 words[29];
} BattleWorkImage;

/* Copies the battle work record into a queued slot and arms the active actor. */
MATCH void func_800A87D4(void) {
    u8*              kind;
    u8*              work;
    BattleWorkImage* slot;
    u32              index;

    index = Battle_AllocEffect(0, 18);
    if ((index & BYTE_MASK) != GAME_NONE) {
        slot                                             = (BattleWorkImage*)&g_BattleEffects[index & BYTE_MASK];
        /* one struct copy (the 16-byte block-move loop), read through the non-volatile cell */
        *slot                                            = *(BattleWorkImage*)g_BattleWorkCell;
        g_BattleEffects[index & BYTE_MASK].unk_06        = 0;
        g_BattleEffects[index & BYTE_MASK].handler_index = 0x12;
        g_BattleEffects[index & BYTE_MASK].header.mode   = 0;
        g_BattleEffects[index & BYTE_MASK].header.step   = 0;
        g_BattleEffects[index & BYTE_MASK].unk_03        = 0;
        g_BattleEffects[index & BYTE_MASK].unk_04        = 0;
        g_BattleEffects[index & BYTE_MASK].header.flags  = g_BattleEffects[index & BYTE_MASK].header.flags & 0xBF;
        work                                             = TASK_BYTES;
        g_BattleEffects[index & BYTE_MASK].target.bytes  = work;
        g_BattleEffects[index & BYTE_MASK].unk_0B        = work[0xB];
        work                                             = TASK_BYTES;
        if (work[0xB] != 0) {
            work[0xB]--;
        }
    }
    kind = (u8*)&g_Battle.target_selector;
    if (*kind < 3) {
        func_800AF2B4((BattleRange*)&g_Game.members[*kind], 0x50);
        if (func_800AF5FC((BattleRange*)&g_Game.members[*kind], 0x10000) != 0) {
            Actor_SelectScript((TASK_BYTES[8] + 0x44) & BYTE_MASK);
            Battle_MarkDamaged(*kind);
            work = TASK_BYTES;
            work[1]++;
        }
    } else {
        func_800AF2B4((BattleRange*)&((volatile BattleEnemyRecord*)g_BattleEnemies)[*kind], 0x50);
        if (func_800AF5FC((BattleRange*)&((volatile BattleEnemyRecord*)g_BattleEnemies)[*kind], 0x10000) != 0) {
            Actor_SelectScript((TASK_BYTES[8] + 0x44) & BYTE_MASK);
            Battle_MarkDamaged(*kind);
            work = TASK_BYTES;
            work[1]++;
        }
    }
    func_801DEE4C();
}
