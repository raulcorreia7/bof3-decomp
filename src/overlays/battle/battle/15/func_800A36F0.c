#include "battle_15.h"

/* Non-volatile scratchpad work cell (0x1F800044), read/saved/restored around
 * the update exactly as the loader expects. */

/* Applies the battler's status masks, updates shared defence values when the
 * magic-defence bit changes, and restores the active work pointer. */
MATCH u16 func_800A36F0(u8 battler_index, u16 flags) {
    u16 status;
    u32 saved_work;

    if (BATTLER_IS_PLAYER(battler_index)) {
        status = g_Game.members[battler_index].chr.status;
    } else {
        status = ENEMY_COMBATANT(battler_index).status;
    }

    if (flags & STATUS_KO) {
        status &= ~STATUS_KO;
    }
    if (flags & STATUS_POISONED) {
        status &= ~STATUS_POISONED;
    }
    if (flags & 0x1u) {
        status &= 0xFFFEu;
    }
    if (flags & 0x2u) {
        status &= 0xFFFDu;
    }
    if (flags & STATUS_PARALYZED) {
        status &= ~STATUS_PARALYZED;
    }
    if (flags & STATUS_SLEEPING) {
        status &= ~STATUS_SLEEPING;
    }
    if (flags & STATUS_BLIND) {
        status &= ~STATUS_BLIND;
    }
    if (flags & STATUS_SILENCED) {
        status &= ~STATUS_SILENCED;
    }
    if (flags & 0x800u) {
        status &= 0xF7FFu;
    }

    if ((flags & STATUS_CONFUSED) && (status & STATUS_CONFUSED)) {
        u32 slot;

        status &= ~STATUS_CONFUSED;
        slot = battler_index;
        if (BATTLER_IS_PLAYER(battler_index)) {
            g_Game.members[slot].pos.x.fixed = g_BattleTemplateStats[slot].defence[0];
            g_Game.members[slot].pos.y.fixed = g_BattleTemplateStats[slot].defence[1];
            g_Game.members[slot].pos.z.fixed = g_BattleTemplateStats[slot].defence[2];
        } else {
            ENEMY_COMBATANT(slot).pos.x.fixed = g_BattleTemplateStats[slot].defence[0];
            ENEMY_COMBATANT(slot).pos.y.fixed = g_BattleTemplateStats[slot].defence[1];
            ENEMY_COMBATANT(slot).pos.z.fixed = g_BattleTemplateStats[slot].defence[2];
        }
    }

    if (BATTLER_IS_PLAYER(battler_index)) {
        volatile u8* battler;
        battler = (u8*)(&g_Game.members[battler_index]);
        GFX_FreePaletteFadeTarget(battler);
        saved_work                               = g_BattleWorkCell;
        g_Game.members[battler_index].chr.status = status;
        g_BattleWorkCell                         = battler;
        func_801DDAB4(g_Game.members[battler_index].chr.status);
    } else {
        volatile u8* battler;
        battler = (u8*)(&((volatile BattleEnemy*)g_BattleEnemies)[battler_index]);
        GFX_FreePaletteFadeTarget(battler);
        saved_work                            = g_BattleWorkCell;
        ENEMY_COMBATANT(battler_index).status = status;
        g_BattleWorkCell                      = battler;
        func_801DDAB4(ENEMY_COMBATANT(battler_index).status);
    }

    g_BattleWorkCell = saved_work;
    return status;
}

/* Local weak bindings (same mechanism as symbols.c) so the diff link step
 * resolves the semantic names; they do not affect compilation. */
