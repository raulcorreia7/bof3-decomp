#include "start_08.h"

extern u8 D_80148656;

MATCH void func_801D3174(void) {
    u8* base;
    u8  mode;
    u8* step;
    u8* row;
    u8* pair;
    s32 trigger;
    u8  old_cursor;
    s8  step_down;
    u8  step_up;
    u8  entry;
    u8  counter;
    u8  saved;
    u8* count;
    s32 result;
    s32 offset;
    u16 pad;

    Menu_DrawClutStrip(g_WindowClut);
    step = &g_UiPanelTasks[13].unk_08;
    mode = 3;
    if (D_801ED618 == 0) {
        mode = 1;
    }
    *step = mode;
    base  = step;
    base -= 8;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id =
        Item_GetDescription(g_UiPanelTasks[13].unk_0A, g_ItemCategoryIds[g_UiPanelTasks[13].unk_0A][g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]);
    pad                                            = g_PadStates[0].pressed;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vx + 7;
    offset                                         = (g_UiPanelTasks[13].unk_0C - g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) * 13 + 0x1A;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vy + offset;
    trigger                                        = INPUT_REPEATED(pad, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if (trigger & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.tabs                 = 0x32;
        s_ChoiceMenuCursors[g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A] = g_UiPanelTasks[13].unk_0C;
        s_ChoiceMenuValues[g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A]  = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        step_down                                                          = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A - 1;
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A                      = step_down;
        if (step_down < 0) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 3;
        }
        /* Both step directions converge on the shared reload block. */
        goto store_selection;
    }
    if (trigger & PADLright) {
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.tabs = 0x31;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        s_ChoiceMenuCursors[g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A] = g_UiPanelTasks[13].unk_0C;
        s_ChoiceMenuValues[g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A]  = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        step_up                                                            = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A + 1;
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A                      = step_up;
        if ((u32)(step_up & BYTE_MASK) >= 4U) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 0;
        }
    /* Shared tail of both cursor-step directions. */
    store_selection:
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = s_ChoiceMenuCursors[g_UiPanelTasks[13].unk_0A];
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = s_ChoiceMenuValues[g_UiPanelTasks[13].unk_0A];
        return;
    }
    old_cursor = g_UiPanelTasks[13].unk_0C;
    if (trigger & PADLup) {
        if (old_cursor != 0) {
            g_UiPanelTasks[13].unk_0C = old_cursor - 1;
        }
        if (g_UiPanelTasks[13].unk_0C < g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0xF0;
        }
    } else if (trigger & PADLdown) {
        if (old_cursor < 0x7F) {
            g_UiPanelTasks[13].unk_0C = old_cursor + 1;
        }
        if (g_UiPanelTasks[13].unk_0C >= g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0x10;
        }
    } else if (trigger & PADL1) {
        u8 group = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        if (group == 0) {
            g_UiPanelTasks[13].unk_0C = 0;
        } else if (group < 9) {
            g_UiPanelTasks[13].unk_0C                     = old_cursor - group;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0;
        } else {
            g_UiPanelTasks[13].unk_0C = old_cursor - 9;
            g_UiPanelTasks[13].unk_0B = group - 9;
        }
    } else if (trigger & PADR1) {
        u8 group = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        if (group == 0x77) {
            g_UiPanelTasks[13].unk_0C = 0x7F;
        } else if (group >= 0x6F) {
            g_UiPanelTasks[13].unk_0C = old_cursor + (0x77 - group);
            g_UiPanelTasks[13].unk_0B = 0x77;
        } else {
            g_UiPanelTasks[13].unk_0C = old_cursor + 9;
            g_UiPanelTasks[13].unk_0B = group + 9;
        }
    }
    s_ChoiceMenuCursors[base[0xA]] = base[0xC];
    s_ChoiceMenuValues[base[0xA]]  = base[0xB];
    if (old_cursor != base[0xC]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    row  = g_ItemCategoryIds[base[0xA]] + base[0xC];
    pair = g_ItemCategoryCounts[base[0xA]] + base[0xC];
    if (((MenuChoicePanel*)base)->confirm_timer != 0) {
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*row != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            if (D_801ED618 == 0) {
                if ((Item_PassesTest(base[8], CHAR_ID_RYU_YOUNG, base[0xA], *row) & BYTE_MASK) != 0) {
                    entry = *row;
                    if (g_Items[entry].flags & ITEM_STORY_ITEM) {
                        result = func_801E8C9C(0, entry, 0) & BYTE_MASK;
                        if (result == 0 || result == 4) {
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                            if (TIMER_EXPIRED(*pair)) {
                                *row = 0;
                            }
                        } else {
                            /* Result outside the accepted set reports failure. */
                            goto fail;
                        }
                    } else {
                        saved                                          = base[0xC];
                        D_80148656                                     = 0;
                        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
                        counter                                        = g_MenuStep.sub_step + 4;
                        /* Both success arms converge on the commit block. */
                        goto commit;
                    }
                } else {
                    /* The confirm call rejected the selection. */
                    goto fail;
                }
            } else {
                if ((Item_PassesTest(base[8], CHAR_ID_RYU_YOUNG, base[0xA], g_ItemCategoryIds[base[0xA]][base[0xC]]) & BYTE_MASK) != 0) {
                    saved      = base[0xC];
                    D_8014865B = 0;
                    counter    = g_MenuStep.sub_step + 3;
                /* Shared tail of both selection-commit arms. */
                commit:
                    base[0xD]           = saved;
                    g_MenuStep.sub_step = counter;
                    return;
                }
                /* The row has no selectable entry. */
                goto fail;
            }
        } else {
        /* Failure path of the confirm mask queues the error cue. */
        fail:
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        count = &g_MenuStep.sub_step;
        *count -= 1;
    }
}
