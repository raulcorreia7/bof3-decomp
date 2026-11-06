#include "battle_15.h"

/* The 0x74 bytes of the work record that a queued slot copies. */
typedef struct BattleWorkImage {
    u32 words[0x1D];
} BattleWorkImage;

/* Copies the battle work record into a queued slot and arms the active actor. */
MATCH void func_800A87D4(void) {
    u8*              kind;
    u8*              work;
    BattleWorkImage* slot;
    u32              index;

    index = Battle_AllocEffect(0, 0x12);
    if ((index & 0xFF) != GAME_NONE) {
        slot                                        = (BattleWorkImage*)&g_BattleEffects[index & 0xFF];
        /* one struct copy (the 16-byte block-move loop), read through the non-volatile cell */
        *slot                                       = *(BattleWorkImage*)g_BattleWorkCell;
        g_BattleEffects[index & 0xFF].unk_06        = 0;
        g_BattleEffects[index & 0xFF].handler_index = 0x12;
        g_BattleEffects[index & 0xFF].header.mode   = 0;
        g_BattleEffects[index & 0xFF].header.step   = 0;
        g_BattleEffects[index & 0xFF].unk_03        = 0;
        g_BattleEffects[index & 0xFF].unk_04        = 0;
        g_BattleEffects[index & 0xFF].header.flags  = g_BattleEffects[index & 0xFF].header.flags & 0xBF;
        work                                        = TASK_BYTES;
        g_BattleEffects[index & 0xFF].target.bytes  = work;
        g_BattleEffects[index & 0xFF].unk_0B        = work[0xB];
        work                                        = TASK_BYTES;
        if (work[0xB] != 0) {
            work[0xB]--;
        }
    }
    kind = (u8*)&g_BattleTargetSelector;
    if (*kind < 3) {
        func_800AF2B4((BattleRange*)&g_BattlePartyBattlers[*kind], 0x50);
        if (func_800AF5FC((BattleRange*)&g_BattlePartyBattlers[*kind], 0x10000) != 0) {
            Actor_SelectScript((TASK_BYTES[8] + 0x44) & 0xFF);
            func_800A9820(*kind);
            work = TASK_BYTES;
            work[1]++;
        }
    } else {
        func_800AF2B4((BattleRange*)&((volatile BattleEnemyRecord*)g_BattleEnemies)[*kind], 0x50);
        if (func_800AF5FC((BattleRange*)&((volatile BattleEnemyRecord*)g_BattleEnemies)[*kind], 0x10000) != 0) {
            Actor_SelectScript((TASK_BYTES[8] + 0x44) & 0xFF);
            func_800A9820(*kind);
            work = TASK_BYTES;
            work[1]++;
        }
    }
    func_801DEE4C();
}
