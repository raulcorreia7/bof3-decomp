/* When the effect timer runs out, moves the effect onto the battler that slot byte 0x04 names (party slots first, then
 * enemy slots), projects the battle range and launches the sparkles of the kind g_BattleEffectBattler names: the kind's
 * count from EFFECT_SPARKLE_COUNTS, each group of four held back by the kind's EFFECT_SPARKLE_DELAYS step more. */
/* func_801EF06C (magic073), func_801EF058 (magic074) */
/* The statements of the burst; each member declares PartyMember* battler, u8 slot and u8 index, count and i. */
#define EFFECT_LAUNCH_SPARKLE_BURST()                                                                                        \
    count          = g_Task->unk_09 - 1;                                                                                     \
    g_Task->unk_09 = count;                                                                                                  \
    if (count == 0) {                                                                                                        \
        index = g_Task->unk_04;                                                                                              \
        if (index < BATTLE_PARTY_CHARACTERS_COUNT) {                                                                         \
            battler = &g_Game.members[index];                                                                                \
        } else {                                                                                                             \
            battler = (PartyMember*)(g_BattleEnemies + index * BATTLE_ENEMY_STRIDE);                                         \
        }                                                                                                                    \
        g_Task->facing      = battler->facing;                                                                               \
        g_Task->pos.x.fixed = battler->pos.x.fixed;                                                                          \
        g_Task->pos.y.fixed = battler->pos.y.fixed;                                                                          \
        g_Task->pos.z.fixed = battler->pos.z.fixed;                                                                          \
        Battle_ProjectRange();                                                                                               \
        g_Task->param.unk_0B = 0;                                                                                            \
        g_Task->unk_09       = 8;                                                                                            \
        g_Task->timer        = 0;                                                                                            \
        g_Task->header.step += 1;                                                                                            \
        for (i = 0; i < EFFECT_SPARKLE_COUNTS[g_BattleEffectBattler->unk_04]; i++) {                                         \
            slot = BMagic_AllocEffect();                                                                                     \
            if (slot != 0xFF) {                                                                                              \
                BMAGIC_EFFECT_SLOTS[slot].battler     = g_Task;                                                              \
                BMAGIC_EFFECT_SLOTS[slot].header.mode = 0;                                                                   \
                BMAGIC_EFFECT_SLOTS[slot].header.step = 0;                                                                   \
                BMAGIC_EFFECT_SLOTS[slot].unk_03      = rand() & 3;                                                          \
                BMAGIC_EFFECT_SLOTS[slot].unk_04      = g_BattleEffectBattler->unk_04;                                       \
                BMAGIC_EFFECT_SLOTS[slot].unk_07      = i;                                                                   \
                BMAGIC_EFFECT_SLOTS[slot].timer_05    = EFFECT_SPARKLE_DELAYS[g_BattleEffectBattler->unk_04] * (i >> 2) + 1; \
                g_Task->param.unk_0B += 1;                                                                                   \
            }                                                                                                                \
        }                                                                                                                    \
    }
