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

    Menu_DrawClutStrip(D_80144953);
    step = &D_8014850C;
    mode = 3;
    if (D_801ED618 == 0) {
        mode = 1;
    }
    *step = mode;
    base  = step;
    base -= 8;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(D_8014850E, D_801C893C[D_8014850E][g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]);
    pad                                                         = g_InputPressed;
    /* FAKE: keeps the pad load ahead of the panel stores. */
    FAKE_BARRIER();
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = (u16)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.x + 7;
    offset                                           = (D_80148510 - g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) * 13 + 0x1A;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y  = (u16)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.y + offset;
    trigger                                          = INPUT_REPEATED(pad, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if (trigger & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].u.list.tabs                 = 0x32;
        s_ChoiceMenuCursors[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A] = D_80148510;
        s_ChoiceMenuValues[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A]  = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        step_down                                                            = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A - 1;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A                      = step_down;
        if (step_down < 0) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 3;
        }
        /* Both step directions converge on the shared reload block. */
        goto store_selection;
    }
    if (trigger & PADLright) {
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].u.list.tabs = 0x31;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        s_ChoiceMenuCursors[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A] = D_80148510;
        s_ChoiceMenuValues[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A]  = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        step_up                                                              = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A + 1;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A                      = step_up;
        if ((u32)(step_up & BYTE_MASK) >= 4U) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 0;
        }
    /* Shared tail of both cursor-step directions. */
    store_selection:
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = s_ChoiceMenuCursors[D_8014850E];
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = s_ChoiceMenuValues[D_8014850E];
        return;
    }
    old_cursor = D_80148510;
    if (trigger & PADLup) {
        if (old_cursor != 0) {
            D_80148510 = old_cursor - 1;
        }
        if (D_80148510 < g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0xF0;
        }
    } else if (trigger & PADLdown) {
        if (old_cursor < 0x7F) {
            D_80148510 = old_cursor + 1;
        }
        if (D_80148510 >= g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0x10;
        }
    } else if (trigger & 0x4) {
        u8 group = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        if (group == 0) {
            D_80148510 = 0;
        } else if (group < 9) {
            D_80148510                                      = old_cursor - group;
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0;
        } else {
            D_80148510 = old_cursor - 9;
            D_8014850F = group - 9;
        }
    } else if (trigger & 0x8) {
        u8 group = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        if (group == 0x77) {
            D_80148510 = 0x7F;
        } else if (group >= 0x6F) {
            D_80148510 = old_cursor + (0x77 - group);
            D_8014850F = 0x77;
        } else {
            D_80148510 = old_cursor + 9;
            D_8014850F = group + 9;
        }
    }
    s_ChoiceMenuCursors[base[0xA]] = base[0xC];
    s_ChoiceMenuValues[base[0xA]]  = base[0xB];
    if (old_cursor != base[0xC]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    row  = D_801C893C[base[0xA]] + base[0xC];
    pair = D_801C8950[base[0xA]] + base[0xC];
    if (((MenuChoicePanel*)base)->confirm_gate != 0) {
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*row != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            if (D_801ED618 == 0) {
                if ((func_801AF494(base[8], CHAR_ID_RYU_YOUNG, base[0xA], *row) & BYTE_MASK) != 0) {
                    entry = *row;
                    if (g_Items[entry].flags & 0x10) {
                        result = func_801E8C9C(0, entry, 0) & BYTE_MASK;
                        if (result == 0 || result == 4) {
                            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                            if (TIMER_EXPIRED(*pair)) {
                                *row = 0;
                            }
                        } else {
                            /* Result outside the accepted set reports failure. */
                            goto fail;
                        }
                    } else {
                        saved                                            = base[0xC];
                        D_80148656                                       = 0;
                        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
                        counter                                          = g_MenuStep.sub_step + 4;
                        /* Both success arms converge on the commit block. */
                        goto commit;
                    }
                } else {
                    /* The confirm call rejected the selection. */
                    goto fail;
                }
            } else {
                if ((func_801AF494(base[8], CHAR_ID_RYU_YOUNG, base[0xA], D_801C893C[base[0xA]][base[0xC]]) & BYTE_MASK) != 0) {
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
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        }
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        count = &g_MenuStep.sub_step;
        *count -= 1;
    }
}
