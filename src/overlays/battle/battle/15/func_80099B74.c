#include "battle_15.h"

/* The command ring holds sixteen handles. */
#define BATTLE_RING_SLOT_MASK 0xF

/* nonmatching unmeasured: tried the pad-state address: retail keeps it in s0 and re-reads the pad state through that
 * register, the candidate reloads the address for each use; tried: the resource select split from the ring store, a
 * pad-state pointer local, one scratchpad read, per-use masks; resume: a source shape that keeps the pad-state address
 * in s0 and reads the pad state through it. */
#ifdef NON_MATCHING
NON_MATCHING void func_80099B74(void) {
    s32  pad;
    u16* pad_state;
    u16  keys;
    u32  resource;
    u8*  resource_id;
    u8   slot;
    u16  choice;
    u8   prev;
    u8*  row_p;
    u8   next;
    /* FAKE: retail reserves 0x20 unused frame bytes. */
    STACK_PADS(u8, 0x28);

    if (g_BattlePanelMode == 0) {
        D_801485DC = 1;
        D_801485E0 = (u16)D_801485BC + 6;
        D_801485E2 = (u16)D_801485BE + ((g_BattleItemRow * 0xD) + 0x57);
    } else {
        D_801485DC = 0;
    }
    resource = 0x32;
    if (D_8014862E == 0) {
        resource = 0x30;
    }
    resource_id                                                = Resource_GetText(resource);
    D_801EB5B4[((D_801EC328 - 1) & BATTLE_RING_SLOT_MASK) * 2] = resource_id;
    pad_state                                                  = &g_InputPressed;
    pad                                                        = INPUT_REPEATED(*pad_state, (PADLup | PADLdown));
    keys                                                       = *pad_state;
    if (keys & g_InputMasks[INPUT_SLOT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        g_BattlePanelMode   = 1;
        g_BattleChoicePhase = 3;
        D_80148624          = 0;
        D_801483C0          = 1;
        D_801485DC          = 0;
        g_BattleUIStep      = 1;
        g_BattleUIState     = 0;
        return;
    }
    if (keys & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        if (g_BattleTargetCursorCol != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            slot = FIELD(u8, g_BattleMessageSlot, 0x5u);
            g_BattlePartyBattlers[slot].turn.damage_flags.volatile_value =
                g_BattlePartyBattlers[slot].turn.damage_flags.volatile_value | 0x4000;
            *(u16*)((u8*)D_80145FAA + FIELD(u8, g_BattleMessageSlot, 0x5u) * BATTLE_PARTY_STRIDE) =
                *(volatile u16*)&g_BattleTargetCursorCol;
            choice                 = *(volatile u16*)&g_BattleTargetCursorCol;
            D_801EB4D8->command.id = choice;
            resource_id = Resource_GetText(Item_GetDescription((s32)(choice >> 8), choice & BYTE_MASK) & HALF_MASK);
            BATTLE_SELECTION_RECORD_HANDLE((D_801EC328 - 1) & BATTLE_RING_SLOT_MASK) = resource_id;
            D_80148597                                                               = 2;
            g_BattlePanelMode                                                        = 1;
            D_801485DC                                                               = 0;
            D_80148624                                                               = 0;
            D_801483C0                                                               = 1;
            g_BattleUIStep                                                           = 7;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
    }
    if ((pad & PADLup) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        row_p  = &g_BattleItemRow;
        prev   = *row_p - 1;
        *row_p = prev;
        if ((s8)prev < 0) {
            *row_p = 5;
        }
    }
    if ((pad & PADLdown) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        row_p  = &g_BattleItemRow;
        next   = *row_p + 1;
        *row_p = next;
        if ((s8)next >= 6) {
            *row_p = 0;
        }
    }
}
#else
INCLUDE_ASM(func_80099B74);
#endif
