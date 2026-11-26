/* When the effect timer runs out, moves the effect onto the battler that slot byte 0x04 names (party slots first, then
 * enemy slots), projects the battle range and launches the sparkles of the type g_BattleEffectBattler names: the type's
 * count from EFFECT_SPARKLE_COUNTS, each group of four held back by the type's EFFECT_SPARKLE_DELAYS step more. */
/* func_801EF06C (magic073), func_801EF058 (magic074) */
/* The statements of the burst; each member declares PartyMember* battler, u8 slot and u8 index, count and i. */
#define EFFECT_LAUNCH_SPARKLE_BURST()                                                                                        \
    count                     = SELF(PartyMember)->unk_09 - 1;                                                               \
    SELF(PartyMember)->unk_09 = count;                                                                                       \
    if (count == 0) {                                                                                                        \
        index = SELF(PartyMember)->unk_04;                                                                                   \
        if (index < BATTLE_PARTY_CHARACTERS_COUNT) {                                                                         \
            battler = &g_Game.members[index];                                                                                \
        } else {                                                                                                             \
            battler = (PartyMember*)(g_BattleEnemies + index * BATTLE_ENEMY_STRIDE);                                         \
        }                                                                                                                    \
        SELF(PartyMember)->facing      = battler->facing;                                                                    \
        SELF(PartyMember)->pos.x.fixed = battler->pos.x.fixed;                                                               \
        SELF(PartyMember)->pos.y.fixed = battler->pos.y.fixed;                                                               \
        SELF(PartyMember)->pos.z.fixed = battler->pos.z.fixed;                                                               \
        Battle_ProjectRange();                                                                                               \
        SELF(PartyMember)->param.unk_0B = 0;                                                                                 \
        SELF(PartyMember)->unk_09       = 8;                                                                                 \
        SELF(PartyMember)->timer        = 0;                                                                                 \
        SELF(PartyMember)->header.step += 1;                                                                                 \
        for (i = 0; i < EFFECT_SPARKLE_COUNTS[g_BattleEffectBattler->unk_04]; i++) {                                         \
            slot = BMagic_AllocEffect();                                                                                     \
            if (slot != 0xFF) {                                                                                              \
                BMAGIC_EFFECT_SLOTS[slot].battler     = g_Self;                                                              \
                BMAGIC_EFFECT_SLOTS[slot].header.mode = 0;                                                                   \
                BMAGIC_EFFECT_SLOTS[slot].header.step = 0;                                                                   \
                BMAGIC_EFFECT_SLOTS[slot].unk_03      = rand() & 3;                                                          \
                BMAGIC_EFFECT_SLOTS[slot].unk_04      = g_BattleEffectBattler->unk_04;                                       \
                BMAGIC_EFFECT_SLOTS[slot].unk_07      = i;                                                                   \
                BMAGIC_EFFECT_SLOTS[slot].timer_05    = EFFECT_SPARKLE_DELAYS[g_BattleEffectBattler->unk_04] * (i >> 2) + 1; \
                SELF(PartyMember)->param.unk_0B += 1;                                                                        \
            }                                                                                                                \
        }                                                                                                                    \
    }
