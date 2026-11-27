#include "boss052_16.h"

/* On the task's mode-7 step-1 event, arms the active enemy's next action: copies
 * the enemy's work record into a fresh battle-effect slot and seeds the slot's
 * handler bytes. */
MATCH void func_800C19CC(void) {
    PartyMember*     task;
    BattleWorkImage* slot;
    BattleWorkImage* row;
    u32              effect_slot;
    s32              offset;
    s32              enemy;

    task = SELF(PartyMember);
    if (task->header.mode != 7 || task->header.step != 1 || task->unk_09 != 0) {
        return;
    }

    effect_slot                                          = Battle_AllocEffect(3, 4);
    offset                                               = (effect_slot & BYTE_MASK) * sizeof(BattleEffect);
    enemy                                                = g_Battle.active_battler;
    slot                                                 = (BattleWorkImage*)((u8*)g_BattleEffects + offset);
    row                                                  = (BattleWorkImage*)((u8*)g_BattleEnemyBattlers + (enemy - BATTLE_PARTY_CHARACTERS_COUNT) * sizeof(EnemyBattler));
    *slot                                                = *row;
    g_BattleEffects[effect_slot & BYTE_MASK].header.mode = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06      = 3;
    g_BattleEffects[effect_slot & BYTE_MASK].effect_type = 4;
    g_BattleEffects[effect_slot & BYTE_MASK].arg.unk_09  = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_29      = 3;
}
