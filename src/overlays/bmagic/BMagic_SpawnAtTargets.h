#ifndef BMAGIC_SPAWN_AT_TARGETS_H
#define BMAGIC_SPAWN_AT_TARGETS_H

/* Clears the effect count, then spawns one effect of kind PART at each target the target check passes on the
 * selected side (the enemies when target selector bit 0x40 is set, else the party), each one 10 ticks after
 * the last, and moves the effect onto the last one spawned. A statement macro: the member declares u32 i,
 * u32 slot and PartyMember* work. */
/* func_801EEC5C (magic097), func_801EEC5C (magic098) */
#define BMAGIC_SPAWN_AT_TARGETS(PART)                                                           \
    slot                 = 0;                                                                   \
    g_Task->param.unk_0B = 0;                                                                   \
    if (g_Battle.target_selector & 0x40) {                                                      \
        for (i = 0; i < 8; i++) {                                                               \
            if (!(Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT)) & BYTE_MASK)) { \
                slot                               = Battle_AllocEffect(1, (PART)) & BYTE_MASK; \
                work                               = g_Task;                                    \
                g_BattleEffects[slot].header.mode  = 0;                                         \
                g_BattleEffects[slot].unk_03       = i;                                         \
                g_BattleEffects[slot].target.party = work;                                      \
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;      \
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;      \
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;      \
                g_BattleEffects[slot].arg.unk_09   = g_Task->param.unk_0B * 10 + 1;             \
                g_Task->param.unk_0B++;                                                         \
            }                                                                                   \
        }                                                                                       \
    } else {                                                                                    \
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {                                   \
            if (!(Battle_SlotIsBlocked((u8)i) & BYTE_MASK)) {                                   \
                slot                               = Battle_AllocEffect(1, (PART)) & BYTE_MASK; \
                work                               = g_Task;                                    \
                g_BattleEffects[slot].header.mode  = 0;                                         \
                g_BattleEffects[slot].unk_03       = i;                                         \
                g_BattleEffects[slot].target.party = work;                                      \
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;             \
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;             \
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;             \
                g_BattleEffects[slot].arg.unk_09   = g_Task->param.unk_0B * 10 + 1;             \
                g_Task->param.unk_0B++;                                                         \
            }                                                                                   \
        }                                                                                       \
    }                                                                                           \
    g_Task->pos.x.fixed = g_BattleEffects[slot].pos.x.fixed;                                    \
    g_Task->pos.y.fixed = g_BattleEffects[slot].pos.y.fixed;                                    \
    g_Task->pos.z.fixed = g_BattleEffects[slot].pos.z.fixed;                                    \
    SND_QueueSelectionFx(0x100);                                                                \
    g_Task->header.mode++;

#endif
