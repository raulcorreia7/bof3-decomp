#ifndef BMAGIC_SPAWN_AT_TARGETS_H
#define BMAGIC_SPAWN_AT_TARGETS_H

/* Clears the effect count, then spawns one effect of type PART at each target the target check passes on the
 * selected side (the enemies when target selector has the enemy side, else the party), each one 10 ticks after
 * the last, and moves the effect onto the last one spawned. A statement macro: the member declares u32 i,
 * u32 slot and PartyMember* work. */
/* func_801EEC5C (magic097), func_801EEC5C (magic098) */
#define BMAGIC_SPAWN_AT_TARGETS(PART)                                                           \
    slot                            = 0;                                                        \
    SELF(PartyMember)->param.unk_0B = 0;                                                        \
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {                                  \
        for (i = 0; i < 8; i++) {                                                               \
            if (!(Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT)) & BYTE_MASK)) { \
                slot                               = Battle_AllocEffect(1, (PART)) & BYTE_MASK; \
                work                               = g_Self;                                    \
                g_BattleEffects[slot].header.mode  = 0;                                         \
                g_BattleEffects[slot].unk_03       = i;                                         \
                g_BattleEffects[slot].target.party = work;                                      \
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;      \
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;      \
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;      \
                g_BattleEffects[slot].arg.unk_09   = SELF(PartyMember)->param.unk_0B * 10 + 1;  \
                SELF(PartyMember)->param.unk_0B++;                                              \
            }                                                                                   \
        }                                                                                       \
    } else {                                                                                    \
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {                                   \
            if (!(Battle_SlotIsBlocked((u8)i) & BYTE_MASK)) {                                   \
                slot                               = Battle_AllocEffect(1, (PART)) & BYTE_MASK; \
                work                               = g_Self;                                    \
                g_BattleEffects[slot].header.mode  = 0;                                         \
                g_BattleEffects[slot].unk_03       = i;                                         \
                g_BattleEffects[slot].target.party = work;                                      \
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;             \
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;             \
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;             \
                g_BattleEffects[slot].arg.unk_09   = SELF(PartyMember)->param.unk_0B * 10 + 1;  \
                SELF(PartyMember)->param.unk_0B++;                                              \
            }                                                                                   \
        }                                                                                       \
    }                                                                                           \
    SELF(PartyMember)->pos.x.fixed = g_BattleEffects[slot].pos.x.fixed;                         \
    SELF(PartyMember)->pos.y.fixed = g_BattleEffects[slot].pos.y.fixed;                         \
    SELF(PartyMember)->pos.z.fixed = g_BattleEffects[slot].pos.z.fixed;                         \
    SND_SEQueueSelection(0x100);                                                                \
    SELF(PartyMember)->header.mode++;

#endif
