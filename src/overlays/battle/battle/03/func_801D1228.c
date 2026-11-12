#include "battle_03.h"

/* Resets the battle: clears the battle state, the living player
 * count and the per-slot rows, then hands the first live battler the work
 * pointer.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801D1228(void) {
    u8* work_row;
    u8* src;
    u8* dest;
    s32 slot;
    s32 index;
    s32 count;
    s32 row_offset;
    s16 flags;

    func_801DE804();
    slot                        = 0;
    g_Battle.living_party_count = 0;
    if (g_Battle.party_count != 0) {
        do {
            if (!(Battle_SlotIsBlocked(slot & BYTE_MASK) & BYTE_MASK)) {
                g_Battle.living_party_count += 1;
            }
            slot += 1;
        } while ((u32)(slot & BYTE_MASK) < (u8)g_Battle.party_count);
    }
    work_row                      = (u8*)g_Game.members;
    *g_Battle.panel_widths        = 8;
    g_BattleMessageSlot           = work_row;
    g_Battle.row_cursor           = 0;
    g_Battle.cursor.panel_entry   = 0;
    D_801462E7                    = 0;
    g_Battle.panel_slot           = 0;
    g_Battle.state                = 0;
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
    D_801463CB                    = 0;
    D_801463CA                    = 0;
    g_Battle.action_lock          = 0;
    D_801463D7                    = 0;
    g_Battle.selection_latch      = 0;
    g_Battle.dragon_form          = 0;
    g_AreaCameraHeightStep        = 0;
    slot                          = 0;
    func_800ABBA4();
    func_801E5A38();
    func_801DDB7C();
    src   = work_row + 0x90;
    dest  = work_row + 0xB0;
    index = 0;
    do {
        row_offset = index * BATTLE_PARTY_STRIDE;
        src        = work_row + 0x90 + row_offset;
        if (ACTOR_IN_USE(g_Game.members[index])) {
            dest                                 = work_row + 0xB0 + row_offset;
            *(BattleStatBlockPart*)(dest)        = *(BattleStatBlockPart*)(src);
            *(BattleStatBlockPart*)(dest + 0x10) = *(BattleStatBlockPart*)(src + 0x10);
            if ((u16) * (D_80145F18 + row_offset) < (u32)((u16) * (D_80145F20 + row_offset) >> 2)) {
                flags = (s16)(*(u16*)(D_80145F10 + row_offset) | 0x2000);
            } else {
                flags = (s16)(*(u16*)(D_80145F10 + row_offset) & 0xDFFF);
            }
            *(u16*)(D_80145F10 + row_offset)                       = flags;
            count                                                  = 0;
            index                                                  = slot & BYTE_MASK;
            src                                                    = work_row + 0x90 + index * BATTLE_PARTY_STRIDE;
            g_Game.members[index].turn.damage_flags.value          = 0;
            g_Game.members[index].turn.action_flags.volatile_value = 0;
            g_Game.members[index].turn.command.type                = 0;
            *(u8*)(&D_80145FB1 + index * 0x140)                    = 0;
            *(u8*)(&D_80145FC6 + index * 0x140)                    = 0;
            *(u8*)(&D_80145FC7 + index * 0x140)                    = 0;
            *(u8*)(&D_80145FC8 + index * 0x140)                    = 0;
            *(u8*)(&D_80145FC9 + index * 0x140)                    = 0;
            count                                                  = 0;
            do {
                *(work_row + 0x12C + index * 0x140 + count) = 0;
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
        row_offset = index * BATTLE_PARTY_STRIDE;
        dest       = D_80145F20 + row_offset;
        if (ACTOR_IN_USE(g_Game.members[index])) {
            src                                  = D_80145F20 + 0x20 + row_offset;
            *(BattleStatBlockPart*)(dest)        = *(BattleStatBlockPart*)(src);
            *(BattleStatBlockPart*)(dest + 0x10) = *(BattleStatBlockPart*)(src + 0x10);
        }
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 3U);
    slot  = 0;
    index = 0;
    do {
        slot += 1;
        row_offset                                   = index * 2;
        MEM_PTR(u16, 0x80039600u)[0xF0 + row_offset] = MEM_PTR(u16, 0x80035600u)[0xF0 + row_offset];
        index                                        = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 0x10U);
    GFX_CopyPalette(0x1A);
    GFX_CopyPalette(0x1B);
    slot = 0;
    do {
        if ((u32)slot < 3U) {
            row_offset = (((s32)slot * 4) + slot) << 6;
            if (ACTOR_IN_USE(g_Game.members[slot])) {
                g_Task = g_Game.members + row_offset;
                goto found; /* joins the shared work-pointer exit */
            }
        } else if (!(Battle_SlotIsBlocked((u32)slot) & BYTE_MASK) && (g_Battle.encounter != 37)) {
            g_Task = (((((s32)(((s32)slot * 8) + slot) * 4) - slot) * 8) + g_BattleEnemies);
        found: /* the live battler's work pointer */
            GFX_UploadPaletteRows();
        }
        slot += 1;
    } while ((u32)(slot & BYTE_MASK) < 0xBU);
    slot = 0;
    if (BATTLE_IS_RANDOM()) {
        EMI_LoadArchive(g_GameAreaId + EMI_SLOT_ENEMY);
        slot = 0;
    }
    index = slot & BYTE_MASK;
    do {
        *(s32*)(D_80146364 + index) = 0;
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 0x10U);
    if (BATTLE_IS_SCRIPTED()) {
        g_Battle.boss_event_hook(BOSS_EVENT_BATTLE_RESET);
    }
    g_Battle.phase.step += 1;
}
#else
INCLUDE_ASM(func_801D1228);
#endif
