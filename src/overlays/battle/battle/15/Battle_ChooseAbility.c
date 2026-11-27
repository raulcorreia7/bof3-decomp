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
NON_MATCHING void Battle_ChooseAbility(void) {
    u8*                     phase;
    BattleSelectionScratch* sel;
    BattleSelectionGroup*   group;
    u8*                     message;
    u8*                     entry;
    s32                     trigger;
    s32                     ring_index;
    u8*                     handle;
    u8                      type;
    s32                     cursor;

    phase = (u8*)&g_BattleChoicePhase;
    if (*phase != 0) {
        return;
    }
    sel        = (BattleSelectionScratch*)((u8*)&g_BattleChoicePhase - 3);
    D_801485DC = 1u;
    D_801485E0 = g_UIPanelTasks[16].pos.vx + 7u;
    D_801485E2 = g_UIPanelTasks[16].pos.vy + ((g_UIPanelTasks[16].unk_0C - sel->scroll_base) * 13 + 0x1A);
    trigger    = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL | PADL1 | PADR1);
    if ((g_BattleActorTurn->action_flags.value & (BATTLER_ACTION_DRAGON_FORM | BATTLER_ACTION_DRAGON_FORM_CONTROLLED)) != (u32)BATTLER_ACTION_DRAGON_FORM) {
        if ((trigger & PADLleft) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            g_UIPanelTasks[16].unk_09 = 0x32u;
            if ((s8)--g_UIPanelTasks[16].unk_0B < 0) {
                g_UIPanelTasks[16].unk_0B = 3u;
            }
        } else if ((trigger & PADLright) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            g_UIPanelTasks[16].unk_09 = 0x31u;
            if (++g_UIPanelTasks[16].unk_0B >= 4u) {
                g_UIPanelTasks[16].unk_0B = 0u;
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
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    message                           = (u8*)&D_80148656;
    /* The group index/cursor pair sits 0xB bytes into the same scratch block. */
    sel                               = (BattleSelectionScratch*)((u8*)sel + 0xB);
    group                             = (BattleSelectionGroup*)sel;
    entry                             = Party_GetAbilities(message[0], group->index, 1);
    type                              = entry[group->cursor];
    handle                            = UI_MessageGetText(*(u16*)(D_801CA71E + type * 0x14));
    ring_index                        = (D_801EC328 - 1) & 0xF;
    g_BattleMessages[ring_index].text = handle;
    if ((s16)g_UIPanelTasks[16].u.addr.unk_12 != 0) {
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_BattleChoicePhase                              = 1u;
        D_801485DC                                       = 0u;
        g_BattleMessages[ring_index].record_type         = 1u;
        ((u8*)D_801454F4)[g_UIPanelTasks[16].unk_0A * 3] = group->index;
        D_801454F5[g_UIPanelTasks[16].unk_0A * 3]        = g_UIPanelTasks[16].u.addr.unk_10;
        D_801454F6[g_UIPanelTasks[16].unk_0A * 3]        = group->cursor;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_Battle.ui_step += 1;
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        BattleTurn* turn;

        if ((Battle_IsAbilityLocked() & BYTE_MASK) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        ((u8*)D_801454F4)[g_UIPanelTasks[16].unk_0A * 3] = group->index;
        D_801454F5[g_UIPanelTasks[16].unk_0A * 3]        = g_UIPanelTasks[16].u.addr.unk_10;
        D_801454F6[g_UIPanelTasks[16].unk_0A * 3]        = group->cursor;
        entry                                            = Party_GetAbilities(message[0], group->index, 1);
        turn                                             = g_BattleActorTurn;
        turn->command.id                                 = entry[group->cursor];
        g_BattleChoicePanel.abilities.state              = 1u;
        g_UIPanelTasks[19].active                        = 0u;
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
INCLUDE_ASM(Battle_ChooseAbility);
#endif
