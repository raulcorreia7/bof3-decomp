#include "battle_03.h"

/* Resets the battle: clears the battle state, the living player
 * count and the per-slot rows, then hands the first live battler the work
 * pointer.
 */
/* nonmatching unmeasured: tried the first draft does not compile (the raw 0x8003xxxx state blocks and the row pointers
 * need views); the first draft cleaned into role-named locals and a local state-block type (47.22%). residual: the
 * register allocation and the row/state address forms still differ from the retail. resume: a source shape that
 * reproduces the retail's row and state-block address forms and its register allocation. */
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
    slot                     = 0;
    g_BattleLivingPartyCount = 0;
    if (g_BattlePartyCount != 0) {
        do {
            if (!(Battle_SlotIsBlocked(slot & BYTE_MASK) & BYTE_MASK)) {
                g_BattleLivingPartyCount += 1;
            }
            slot += 1;
        } while ((u32)(slot & BYTE_MASK) < (u8)g_BattlePartyCount);
    }
    work_row               = (u8*)g_BattlePartyBattlers;
    *g_BattlePanelWidths   = 8;
    g_BattleMessageSlot    = work_row;
    g_BattleRowCursor      = 0;
    g_BattlePanelEntry     = 0;
    D_801462E7             = 0;
    g_BattlePanelSlot      = 0;
    g_BattleState          = 0;
    g_BattleResult         = 0;
    D_801463D0             = 1;
    g_BattleSpoilsZenny    = 0;
    g_BattleSpoilsExp      = 0;
    D_80146326.attempts    = 0;
    g_BattleBossFlags      = 0;
    D_801463BA             = 0;
    g_BattlePendingStatus  = 0;
    D_80146327             = 0;
    D_801463C2             = 0;
    D_801463CB             = 0;
    D_801463CA             = 0;
    g_BattleActionLock     = 0;
    D_801463D7             = 0;
    g_BattleSelectionLatch = 0;
    g_DragonForm           = 0;
    g_AreaCameraHeightStep = 0;
    slot                   = 0;
    func_800ABBA4();
    func_801E5A38();
    func_801DDB7C();
    src   = work_row + 0x90;
    dest  = work_row + 0xB0;
    index = 0;
    do {
        row_offset = index * BATTLE_PARTY_STRIDE;
        src        = work_row + 0x90 + row_offset;
        if (ACTOR_IN_USE(g_BattlePartyBattlers[index])) {
            dest                                 = work_row + 0xB0 + row_offset;
            *(BattleStatBlockPart*)(dest)        = *(BattleStatBlockPart*)(src);
            *(BattleStatBlockPart*)(dest + 0x10) = *(BattleStatBlockPart*)(src + 0x10);
            if ((u16) * (D_80145F18 + row_offset) < (u32)((u16) * (D_80145F20 + row_offset) >> 2)) {
                flags = (s16)(*(u16*)(D_80145F10 + row_offset) | 0x2000);
            } else {
                flags = (s16)(*(u16*)(D_80145F10 + row_offset) & 0xDFFF);
            }
            *(u16*)(D_80145F10 + row_offset)                         = flags;
            count                                                    = 0;
            index                                                    = slot & BYTE_MASK;
            src                                                      = work_row + 0x90 + index * BATTLE_PARTY_STRIDE;
            g_BattlePartyBattlers[index].damage_flags.value          = 0;
            g_BattlePartyBattlers[index].action_flags.volatile_value = 0;
            *(u8*)(&D_80145FA9 + index * 0x140)                      = 0;
            *(u8*)(&D_80145FB1 + index * 0x140)                      = 0;
            *(u8*)(&D_80145FC6 + index * 0x140)                      = 0;
            *(u8*)(&D_80145FC7 + index * 0x140)                      = 0;
            *(u8*)(&D_80145FC8 + index * 0x140)                      = 0;
            *(u8*)(&D_80145FC9 + index * 0x140)                      = 0;
            count                                                    = 0;
            do {
                *(work_row + 0x12C + index * 0x140 + count) = 0;
                count += 1;
            } while ((u32)(count & BYTE_MASK) < 8U);
        }
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 3U);
    slot = 0;
    func_800AAA74();
    index = 0;
    do {
        row_offset = index * BATTLE_PARTY_STRIDE;
        dest       = D_80145F20 + row_offset;
        if (ACTOR_IN_USE(g_BattlePartyBattlers[index])) {
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
            if (ACTOR_IN_USE(g_BattlePartyBattlers[slot])) {
                g_Task = g_BattlePartyBattlers + row_offset;
                goto found; /* joins the shared work-pointer exit */
            }
        } else if (!(Battle_SlotIsBlocked((u32)slot) & BYTE_MASK) && (g_BattleEncounter != 37)) {
            g_Task = (((((s32)(((s32)slot * 8) + slot) * 4) - slot) * 8) + g_BattleEnemies);
        found: /* the live battler's work pointer */
            GFX_UploadPaletteRows();
        }
        slot += 1;
    } while ((u32)(slot & BYTE_MASK) < 0xBU);
    slot = 0;
    if (g_BattleEncounter == 0) {
        EMI_LoaderStreamInitSlot(g_GameAreaId + EMI_SLOT_ENEMY);
        slot = 0;
    }
    index = slot & BYTE_MASK;
    do {
        *(s32*)(D_80146364 + index) = 0;
        slot += 1;
        index = slot & BYTE_MASK;
    } while ((u32)(slot & BYTE_MASK) < 0x10U);
    if (g_BattleEncounter != 0) {
        g_BossBattleEventHook(6U);
    }
    g_BattleStep += 1;
}
#else
INCLUDE_ASM(func_801D1228);
#endif
