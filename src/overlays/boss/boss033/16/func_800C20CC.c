#include "boss033_16.h"

/* The 0x74 bytes of the work record that a queued slot copies. */
typedef struct BattleWorkImage {
    u32 words[0x1D];
} BattleWorkImage;

/* Copies the battle work record into a queued slot and arms the active actor. */
MATCH void func_800C20CC(void) {
    u8*              kind;
    u8*              work;
    BattleWorkImage* slot;
    u32              index;

    index = Battle_AllocEffect(3, 6);
    if ((index & 0xFF) != GAME_NONE) {
        slot                                        = (BattleWorkImage*)&g_BattleEffects[index & 0xFF];
        *slot                                       = *(BattleWorkImage*)g_Task;
        g_BattleEffects[index & 0xFF].unk_06        = 3;
        g_BattleEffects[index & 0xFF].handler_index = 6;
        g_BattleEffects[index & 0xFF].header.mode   = 1;
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
        func_800AF2B4(&g_BattlePartyBattlers[*kind], 0x50);
        if (func_800AF5FC(&g_BattlePartyBattlers[*kind], 0x10000) != 0) {
            Actor_SelectScript(5);
            func_800A9820(*kind);
            work = TASK_BYTES;
            work[2]++;
        }
    } else {
        func_800AF2B4(&g_BattleEnemies[*kind * 0x118], 0x50);
        if (func_800AF5FC(&g_BattleEnemies[*kind * 0x118], 0x10000) != 0) {
            Actor_SelectScript(5);
            func_800A9820(*kind);
            work = TASK_BYTES;
            work[2]++;
        }
    }
    func_8014DAEC();
}
