#include "boss052_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C19CC(void) {
    PartyMember* task;
    u32          effect_slot;
    s32          enemy;
    CopyWords16* src;
    CopyWords16* dst;
    CopyWords16* end;

    task = g_Task;
    if ((FIELD(u32, task, 0) & 0xFFFF00) != 0x10700 || task->unk_09 != 0) {
        return;
    }

    effect_slot = Battle_AllocEffect(3, 4);
    dst         = (CopyWords16*)&g_BattleEffects[effect_slot & BYTE_MASK];
    enemy       = g_Battle.active_battler;
    enemy -= 3;
    src = (CopyWords16*)&g_BattleEnemyBattlers[enemy];
    end = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: keeps the tail word store before slot setup. */
    FAKE_ORDER_LOCK(dst->w[0] = src->w[0]);

    g_BattleEffects[effect_slot & BYTE_MASK].header.mode = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06      = 3;
    g_BattleEffects[effect_slot & BYTE_MASK].step_index  = 4;
    g_BattleEffects[effect_slot & BYTE_MASK].arg.unk_09  = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_29      = 4;
}
#else
INCLUDE_ASM(func_800C19CC);
#endif
