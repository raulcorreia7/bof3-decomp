#include "battle_03.h"

/* Resets the battle: clears the battle state, the living player
 * count and the per-slot rows, then hands the first live battler the work
 * pointer.
 */
/* func_801D1228 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_Reset(void) {
    PartyMember* members;
    u8*          src;
    u8*          dest;
    u8*          living_count;
    u8*          count_ptr;
    u8           slot;
    s32          index;
    s32          count;
    u32          word_offset;
    s16          flags;

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
    members                       = g_Game.members;
    *g_Battle.panel_widths        = 8;
    g_BattleMessageSlot           = (u8*)members;
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
    slot                          = 0;
    func_800ABBA4();
    func_801E5A38();
    func_801DDB7C();
    index = 0;
    do {
        src = (u8*)&members[index].chr.stats;
        if (ACTOR_IN_USE(g_Game.members[index])) {
            dest                    = (u8*)&members[index].chr.base;
            *(Cpy16u*)(dest)        = *(Cpy16u*)(src);
            *(Cpy16u*)(dest + 0x10) = *(Cpy16u*)(src + 0x10);
            if (members[index].chr.hp < (u32)(members[index].chr.stats.max_hp >> 2)) {
                flags = (s16)(members[index].chr.status | 0x2000);
            } else {
                flags = (s16)(members[index].chr.status & 0xDFFF);
            }
            members[index].chr.status                         = flags;
            count                                             = 0;
            index                                             = slot & BYTE_MASK;
            src                                               = (u8*)&members[index].chr.stats;
            members[index].u.turn.damage_flags.value          = 0;
            members[index].u.turn.action_flags.volatile_value = 0;
            members[index].u.turn.command.type                = 0;
            members[index].u.turn.counter                     = 0;
            members[index].charge_counter                     = 0;
            members[index].status_counter                     = 0;
            members[index].focus_counter                      = 0;
            members[index].unk_139                            = 0;
            count                                             = 0;
            do {
                members[index].status.unk_12C[count] = 0;
                count += 1;
            } while ((u32)(count & BYTE_MASK) < 8U);
        }
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 3U);
    slot = 0;
    Battle_ApplyFormationStats();
    index = 0;
    do {
        dest = (u8*)&members[index].chr.stats;
        if (ACTOR_IN_USE(g_Game.members[index])) {
            src                     = (u8*)&members[index].chr.base;
            *(Cpy16u*)(dest)        = *(Cpy16u*)(src);
            *(Cpy16u*)(dest + 0x10) = *(Cpy16u*)(src + 0x10);
        }
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 3U);
    slot  = 0;
    index = 0;
    do {
        slot += 1;
        word_offset                                   = index * 2;
        MEM_PTR(u16, 0x80039600u)[0xF0 + word_offset] = MEM_PTR(u16, 0x80035600u)[0xF0 + word_offset];
        index                                         = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 0x10U);
    GFX_PaletteCopy(0x1A);
    GFX_PaletteCopy(0x1B);
    slot = 0;
    do {
        if ((u32)slot < 3U) {
            if (ACTOR_IN_USE(g_Game.members[slot])) {
                g_Task = &members[slot];
                goto found; /* joins the shared work-pointer exit */
            }
        } else if (!(Battle_SlotIsBlocked((u32)slot) & BYTE_MASK) && (g_Battle.encounter != 37)) {
            g_Task = (((((s32)(((s32)slot * 8) + slot) * 4) - slot) * 8) + g_BattleEnemies);
        found: /* the live battler's work pointer */
            GFX_PaletteUploadRows();
        }
        slot += 1;
    } while ((u32)(slot & BYTE_MASK) < 0xBU);
    slot = 0;
    if (BATTLE_IS_RANDOM()) {
        EMI_ArchiveLoad(g_GameAreaId + EMI_SLOT_ENEMY);
        slot = 0;
    }
    index = slot & BYTE_MASK;
    do {
        *(s32*)(g_Battle.unk_84 + index) = 0;
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 0x10U);
    if (BATTLE_IS_SCRIPTED()) {
        g_Battle.boss_event_hook(BOSS_EVENT_BATTLE_RESET);
    }
    g_Battle.phase.step += 1;
}
#else
INCLUDE_ASM(Battle_Reset);
#endif
