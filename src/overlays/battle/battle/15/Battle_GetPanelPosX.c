#include "battle_15.h"

/* Group index/cursor pair inside the primary battle-selection scratch block. */
typedef struct BattleSelectionGroup {
    u8 index;
    u8 cursor;
} BattleSelectionGroup;

/* Primary battle-selection scratch block; cursor geometry lives at 0x8014857C.
 * The block is addressed from its phase byte at 0x80148573. */
typedef struct BattleSelectionScratch {
    u8  pad_00[0xC];
    u8  cursor_index;
    u8  pad_0D[3];
    s16 scroll_base;
    s16 scroll_delta;
} BattleSelectionScratch;

#ifdef NON_MATCHING
/* FAKE: retail reads D_801454F4 as flat bytes; the owner declares rows. */
/* func_8009704C */
NON_MATCHING void Battle_GetPanelPosX(void) {
    u8*                     phase;
    BattleSelectionScratch* sel;
    BattleSelectionGroup*   group;
    u8*                     message;
    u8*                     entry;
    s32                     trigger;
    s32                     ring_index;
    u8*                     handle;
    u8                      kind;
    s32                     cursor;

    phase = (u8*)&g_BattleChoicePhase;
    if (*phase != 0) {
        return;
    }
    sel        = (BattleSelectionScratch*)((u8*)&g_BattleChoicePhase - 3);
    D_801485DC = 1u;
    D_801485E0 = g_MenuPanelTasks[16].pos.x + 7u;
    D_801485E2 = g_MenuPanelTasks[16].pos.y + ((g_MenuPanelTasks[16].unk_0C - g_MenuPanelTasks[16].u.addr.unk_10) * 13 + 0x1A);
    trigger    = INPUT_GetRepeatedButtons((s32)(g_InputPressed & (INPUT_DIRECTIONAL | PADL1 | PADR1)));
    if ((g_BattleActorTurn->action_flags.value & (COMBATANT_FLAG_DRAGON_FORM | COMBATANT_FLAG_DRAGON_FORM_CONTROLLED)) != (u32)COMBATANT_FLAG_DRAGON_FORM) {
        if ((trigger & PADLleft) != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            g_MenuPanelTasks[16].unk_09 = 0x32u;
            cursor                      = g_MenuPanelTasks[16].unk_0B - 1;
            g_MenuPanelTasks[16].unk_0B = cursor;
            if ((s8)cursor < 0) {
                g_MenuPanelTasks[16].unk_0B = 3u;
            }
        } else if ((trigger & PADLright) != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            g_MenuPanelTasks[16].unk_09 = 0x31u;
            cursor                      = g_MenuPanelTasks[16].unk_0B + 1;
            g_MenuPanelTasks[16].unk_0B = cursor;
            if ((u8)cursor >= 4u) {
                g_MenuPanelTasks[16].unk_0B = 0u;
            }
        }
    }
    cursor = sel->cursor_index;
    if ((trigger & PADLup) != 0) {
        if (cursor != 0) {
            sel->cursor_index = cursor - 1;
        }
        if ((s32)sel->cursor_index < sel->scroll_base) {
            sel->scroll_delta = 0xF0;
        }
    } else if ((trigger & PADLdown) != 0) {
        if (cursor < 9u) {
            sel->cursor_index = cursor + 1;
        }
        if ((s32)sel->cursor_index >= sel->scroll_base + 7) {
            sel->scroll_delta = 0x10;
        }
    } else if ((trigger & 4) != 0) {
        s16 base = sel->scroll_base;

        if (base == 0) {
            sel->cursor_index = 0;
        } else if (base < 7) {
            sel->cursor_index = cursor - base;
            sel->scroll_base  = 0;
        } else {
            sel->cursor_index = cursor - 7;
            sel->scroll_base  = (u16)sel->scroll_base - 7;
        }
    } else if ((trigger & 8) != 0) {
        s16 base = sel->scroll_base;

        if (base == 3) {
            sel->cursor_index = 9;
        } else if (base >= -3) {
            sel->cursor_index = cursor - (base - 3);
            sel->scroll_base  = 3;
        } else {
            sel->cursor_index = cursor + 7;
            sel->scroll_base  = (u16)sel->scroll_base + 7;
        }
    }
    if (cursor != sel->cursor_index) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    message                    = (u8*)&D_80148656;
    /* The group index/cursor pair sits 0xB bytes into the same scratch block. */
    sel                        = (BattleSelectionScratch*)((u8*)sel + 0xB);
    group                      = (BattleSelectionGroup*)sel;
    entry                      = Party_GetAbilities(message[0], group->index, 1);
    kind                       = entry[group->cursor];
    handle                     = Message_GetText(*(u16*)(D_801CA71E + kind * 0x14));
    ring_index                 = (D_801EC328 - 1) & 0xF;
    D_801EB5B4[ring_index * 2] = handle;
    if (g_MenuPanelTasks[16].u.addr.unk_12 != 0) {
        return;
    }
    if ((g_InputPressed & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_BattleChoicePhase                                = 1u;
        D_801485DC                                         = 0u;
        D_801EB5B1[ring_index * 8]                         = 1u;
        ((u8*)D_801454F4)[g_MenuPanelTasks[16].unk_0A * 3] = group->index;
        D_801454F5[g_MenuPanelTasks[16].unk_0A * 3]        = g_MenuPanelTasks[16].u.addr.unk_10;
        D_801454F6[g_MenuPanelTasks[16].unk_0A * 3]        = group->cursor;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        *(volatile u8*)&g_Battle.ui_step += 1;
        return;
    }
    if ((g_InputPressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        BattleTurn* turn;

        if ((Battle_IsAbilityLocked() & BYTE_MASK) != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        ((u8*)D_801454F4)[g_MenuPanelTasks[16].unk_0A * 3] = group->index;
        D_801454F5[g_MenuPanelTasks[16].unk_0A * 3]        = g_MenuPanelTasks[16].u.addr.unk_10;
        D_801454F6[g_MenuPanelTasks[16].unk_0A * 3]        = group->cursor;
        entry                                              = Party_GetAbilities(message[0], group->index, 1);
        kind                                               = entry[group->cursor];
        turn                                               = g_BattleActorTurn;
        turn->command.id                                   = kind;
        g_BattleChoicePhase                                = 1u;
        D_801485DC                                         = 0u;
        if (turn->command.id == 0x97u) {
            g_BattleMessageState              = 2u;
            g_BattleActorTurn->command.target = g_BattleMessageSlot[5];
            g_Battle.phase.sub_step           = 7u;
            g_Battle.ui_step                  = 0u;
            return;
        }
        g_Battle.ui_step = 3u;
    }
}
#else
INCLUDE_ASM(Battle_GetPanelPosX);
#endif
