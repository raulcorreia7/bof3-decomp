/* Clears the effect slot table and spawns one palette fade per selectable battler: the enemy slots when the target
 * selector holds 0x40, the party slots otherwise, each fade starting 28 frames after the one before. */
/* func_801EED18 (magic073, magic074) */
/* The statements of func_801EED18; each member declares u32 slot and u8 i, battler and count, and passes the handler
 * index of the fades and the value for byte 0x04 of the effect. */
#define EFFECT_SPAWN_TARGET_FADES(handler, task_04)                                                \
    count = 0;                                                                                     \
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {                                                    \
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;                                                   \
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;                                                   \
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;                                                   \
    }                                                                                              \
    g_Task->unk_04       = (task_04);                                                              \
    g_Task->param.unk_0B = 0;                                                                      \
    g_Task->header.mode += 1;                                                                      \
    if (g_Battle.target_selector & 0x40) {                                                         \
        for (i = 0; i < 8; i++) {                                                                  \
            battler = i + BATTLE_PARTY_CHARACTERS_COUNT;                                           \
            if (!Battle_SlotIsBlocked(battler)) {                                                  \
                slot                               = Battle_AllocEffect(1, (handler)) & BYTE_MASK; \
                g_BattleEffects[slot].target.party = g_Task;                                       \
                g_BattleEffects[slot].header.mode  = 0;                                            \
                g_BattleEffects[slot].unk_04       = battler;                                      \
                g_BattleEffects[slot].arg.unk_09   = count * 28 + 1;                               \
                count++;                                                                           \
                g_Task->param.unk_0B += 1;                                                         \
            }                                                                                      \
        }                                                                                          \
    } else {                                                                                       \
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {                                      \
            if (!Battle_SlotIsBlocked(i)) {                                                        \
                slot                               = Battle_AllocEffect(1, (handler)) & BYTE_MASK; \
                g_BattleEffects[slot].target.party = g_Task;                                       \
                g_BattleEffects[slot].header.mode  = 0;                                            \
                g_BattleEffects[slot].unk_04       = i;                                            \
                g_BattleEffects[slot].arg.unk_09   = count * 28 + 1;                               \
                count++;                                                                           \
                g_Task->param.unk_0B += 1;                                                         \
            }                                                                                      \
        }                                                                                          \
    }                                                                                              \
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
