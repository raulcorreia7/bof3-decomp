#include "start_08.h"

MATCH void func_801D3D00(void) {
    MenuChoicePanel* panel;
    u8*              state_counter;
    u8               cursor;
    u8               page_start;
    u8               page_start_masked;
    u8               scrolled;
    s32              pressed;
    u32              span;

    Menu_DrawClutStrip(g_WindowClut);
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id =
        Item_GetDescription(g_UiPanelTasks[13].unk_0A, g_ItemCategoryIds[g_UiPanelTasks[13].unk_0A][g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]);
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    g_UiPanelTasks[14].unk_0C                      = 0;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vx + 7;
    span                                           = (g_UiPanelTasks[13].unk_0C - g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) * 0xD + 0x1A;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vy + span;
    panel                                          = &D_80148504;
    pressed                                        = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown | PADL1 | PADR1));
    cursor                                         = g_UiPanelTasks[13].unk_0C;
    if (pressed & PADLup) {
        if (cursor != 0) {
            g_UiPanelTasks[13].unk_0C = cursor - 1;
        }
        if ((u32)g_UiPanelTasks[13].unk_0C < (u32)g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0xF0;
        }
    } else if (pressed & PADLdown) {
        if ((u32)cursor < 0x7FU) {
            g_UiPanelTasks[13].unk_0C = cursor + 1;
        }
        if (g_UiPanelTasks[13].unk_0C >= g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0x10;
        }
    } else if (pressed & PADL1) {
        if ((g_UiPanelTasks[13].unk_0B & BYTE_MASK) == 0) {
            g_UiPanelTasks[13].unk_0C = 0;
        } else if ((u32)(g_UiPanelTasks[13].unk_0B & BYTE_MASK) < 9U) {
            g_UiPanelTasks[13].unk_0C                     = cursor - g_UiPanelTasks[13].unk_0B;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0;
        } else {
            g_UiPanelTasks[13].unk_0C = cursor - 9;
            g_UiPanelTasks[13].unk_0B = g_UiPanelTasks[13].unk_0B - 9;
        }
    } else if (pressed & PADR1) {
        page_start        = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        page_start_masked = page_start & BYTE_MASK;
        if (page_start_masked == 0x77) {
            g_UiPanelTasks[13].unk_0C = 0x7F;
        } else if (page_start_masked >= 0x6F) {
            scrolled                  = cursor + 0x77;
            g_UiPanelTasks[13].unk_0C = scrolled - page_start;
            g_UiPanelTasks[13].unk_0B = 0x77;
        } else {
            g_UiPanelTasks[13].unk_0C = cursor + 9;
            g_UiPanelTasks[13].unk_0B = page_start + 9;
        }
    }
    s_ChoiceMenuCursors[panel->group] = panel->group_cursor;
    s_ChoiceMenuValues[panel->group]  = panel->group_first;
    if (cursor != panel->group_cursor) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (panel->confirm_timer == 0) {
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (panel->drawn_cursor == GAME_NONE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                if (g_ItemCategoryIds[panel->group][panel->group_cursor] != 0) {
                    panel->drawn_cursor = panel->group_cursor;
                    return;
                }
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                return;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Menu_SwapBytes(&g_ItemCategoryIds[panel->group][panel->drawn_cursor], &g_ItemCategoryIds[panel->group][panel->group_cursor]);
            Menu_SwapBytes(&g_ItemCategoryCounts[panel->group][panel->drawn_cursor], &g_ItemCategoryCounts[panel->group][panel->group_cursor]);
            panel->drawn_cursor = 0xFF;
        } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            if (panel->drawn_cursor == GAME_NONE) {
                state_counter  = &g_MenuStep.state;
                *state_counter = *state_counter - 1;
                return;
            }
            panel->drawn_cursor = 0xFF;
        }
    }
}
