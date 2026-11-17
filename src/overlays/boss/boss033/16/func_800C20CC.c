#include "boss033_16.h"

/* Copies the battle work record into a queued slot and arms the active actor. */
MATCH void func_800C20CC(void) {
    u8*              kind;
    u8*              work;
    BattleWorkImage* slot;
    u32              index;

    index = Battle_AllocEffect(3, 6);
    if ((index & BYTE_MASK) != GAME_NONE) {
        slot                                            = (BattleWorkImage*)&g_BattleEffects[index & BYTE_MASK];
        *slot                                           = *(BattleWorkImage*)g_Task;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 3;
        g_BattleEffects[index & BYTE_MASK].step_index   = 6;
        g_BattleEffects[index & BYTE_MASK].header.mode  = 1;
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
    kind = (u8*)&g_Battle.target_selector;
    if (*kind < 3) {
        func_800AF2B4(&g_Game.members[*kind], 0x50);
        if (func_800AF5FC(&g_Game.members[*kind], 0x10000) != 0) {
            Actor_SelectScript(5);
            Battle_MarkDamaged(*kind);
            ((PartyMember*)g_Task)->header.step++;
        }
    } else {
        func_800AF2B4(&g_BattleEnemies[*kind * 0x118], 0x50);
        if (func_800AF5FC(&g_BattleEnemies[*kind * 0x118], 0x10000) != 0) {
            Actor_SelectScript(5);
            Battle_MarkDamaged(*kind);
            ((PartyMember*)g_Task)->header.step++;
        }
    }
    Actor_StepAnimOnce();
}
