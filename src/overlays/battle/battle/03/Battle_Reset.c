#include "battle_03.h"

/* Resets the battle: clears the battle state, the living player
 * count and the per-slot rows, then hands the first live battler the work
 * pointer.
 */
/* func_801D1228 */
MATCH void Battle_Reset(void) {
    u8*  living_count;
    u8*  count_ptr;
    u16* mirror;
    u16* stage;
    u8   slot;
    u8   index;

    func_801DE804();
    slot          = 0;
    living_count  = &g_Battle.living_party_count;
    *living_count = 0;
    if (g_Battle.party_count != 0) {
        count_ptr = living_count;
        do {
            if (!(Battle_SlotIsBlocked(slot & BYTE_MASK) & BYTE_MASK)) {
                *count_ptr += 1;
            }
            slot += 1;
        } while ((u32)(slot & BYTE_MASK) < (u8)g_Battle.party_count);
    }
    g_BattleMessageSlot           = (u8*)g_Game.members;
    g_Battle.panel_widths[0]      = 8;
    g_Battle.selection            = 0;
    g_Battle.cursor.panel_entry   = 0;
    D_801462E7                    = 0;
    g_Battle.panel_slot           = 0;
    g_Battle.flags                = 0;
    g_Battle.outcome.result       = 0;
    D_801463D0                    = 1;
    g_Battle.outcome.reward_zenny = 0;
    g_Battle.outcome.reward_exp   = 0;
    g_Battle.outcome.attempts     = 0;
    g_Battle.boss_flags           = 0;
    D_801463BA                    = 0;
    g_Battle.pending_status       = 0;
    g_Battle.outcome.drop_count   = 0;
    D_801463C2                    = 0;
    g_Battle.unk_EA[1]            = 0;
    g_Battle.unk_EA[0]            = 0;
    g_Battle.action_lock          = 0;
    g_Battle.unk_EF[8]            = 0;
    g_Battle.selection_latch      = 0;
    g_Battle.dragon_form          = 0;
    g_AreaCameraHeightDelta       = 0;
    func_800ABBA4();
    func_801E5A38();
    func_801DDB7C();
    for (slot = 0; slot < 3; slot++) {
        if (ACTOR_IN_USE(g_Game.members[slot])) {
            g_Game.members[slot].chr.base = g_Game.members[slot].chr.stats;
            if (g_Game.members[slot].chr.hp < (u32)(g_Game.members[slot].chr.stats.max_hp >> 2)) {
                g_Game.members[slot].chr.status = g_Game.members[slot].chr.status | 0x2000;
            } else {
                g_Game.members[slot].chr.status = g_Game.members[slot].chr.status & 0xDFFF;
            }
            g_Game.members[slot].u.turn.damage_flags.value          = 0;
            g_Game.members[slot].u.turn.action_flags.volatile_value = 0;
            g_Game.members[slot].u.turn.command.type                = 0;
            g_Game.members[slot].u.turn.counter                     = 0;
            g_Game.members[slot].charge_counter                     = 0;
            g_Game.members[slot].status_counter                     = 0;
            g_Game.members[slot].focus_counter                      = 0;
            g_Game.members[slot].unk_139                            = 0;
            for (index = 0; index < 8; index++) {
                g_Game.members[slot].status.unk_12C[index] = 0;
            }
        }
    }
    Battle_ApplyFormationStats();
    for (slot = 0; slot < 3; slot++) {
        if (ACTOR_IN_USE(g_Game.members[slot])) {
            g_Game.members[slot].chr.stats = g_Game.members[slot].chr.base;
        }
    }
    for (slot = 0; slot < 0x10; slot++) {
        mirror              = GAME_PALETTE_MIRROR_U16;
        stage               = (u16*)GAME_PALETTE_STAGE;
        mirror[0xF0 + slot] = stage[0xF0 + slot];
    }
    GFX_PaletteCopy(0x1A);
    GFX_PaletteCopy(0x1B);
    for (slot = 0; slot < 0xB; slot++) {
        if (slot < 3) {
            if (ACTOR_IN_USE(g_Game.members[slot])) {
                g_Task = &g_Game.members[slot];
                goto found; /* joins the shared work-pointer exit */
            }
        } else if (!(Battle_SlotIsBlocked(slot) & BYTE_MASK) && (g_Battle.encounter != 37)) {
            g_Task = g_BattleEnemies + ((slot * 36u - slot) * 8u);
        found: /* the live battler's work pointer */
            GFX_PaletteUploadRows();
        }
    }
    if (BATTLE_IS_RANDOM()) {
        EMI_ArchiveLoad(g_GameAreaId + EMI_SLOT_ENEMY);
        slot = 0;
    }
    for (slot = 0; slot < 0x10; slot++) {
        g_Battle.unk_84[slot] = 0;
    }
    if (BATTLE_IS_SCRIPTED()) {
        g_Battle.boss_event_hook(BOSS_EVENT_BATTLE_RESET);
    }
    g_Battle.phase.step += 1;
}
