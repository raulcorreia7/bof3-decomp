#include "start_08.h"

MATCH void func_801D4564(void) {
    MenuChoicePanel* panel;
    u8*              state_counter;
    u8               cursor;
    u8               page_start;
    u8               page_start_masked;
    u8               scrolled;
    s32              pressed;
    u32              span;

    Menu_DrawClutStrip(D_80144953);
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(D_8014850E, D_801C893C[D_8014850E][g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]);
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.x             = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.x + 7;
    span                                                      = (D_80148510 - g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) * 0xD + 0x1A;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.y             = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.y + span;
    panel                                                     = &D_80148504;
    pressed                                                   = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown | PADL1 | PADR1));
    cursor                                                    = D_80148510;
    if (pressed & PADLup) {
        if (cursor != 0) {
            D_80148510 = cursor - 1;
        }
        if ((u32)D_80148510 < (u32)g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0xF0;
        }
    } else if (pressed & PADLdown) {
        if ((u32)cursor < 0x1FU) {
            D_80148510 = cursor + 1;
        }
        if (D_80148510 >= g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0x10;
        }
    } else if (pressed & PADL1) {
        if ((D_8014850F & BYTE_MASK) == 0) {
            D_80148510 = 0;
        } else if ((u32)(D_8014850F & BYTE_MASK) < 9U) {
            D_80148510                                    = cursor - D_8014850F;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0;
        } else {
            D_80148510 = cursor - 9;
            D_8014850F = D_8014850F - 9;
        }
    } else if (pressed & PADR1) {
        page_start        = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        page_start_masked = page_start & BYTE_MASK;
        if (page_start_masked == 0x17) {
            D_80148510 = 0x1F;
        } else if (page_start_masked >= 0xF) {
            scrolled   = cursor + 0x17;
            D_80148510 = scrolled - page_start;
            D_8014850F = 0x17;
        } else {
            D_80148510 = cursor + 9;
            D_8014850F = page_start + 9;
        }
    }
    s_ChoiceMenuCursors[panel->group] = panel->group_cursor;
    s_ChoiceMenuValues[panel->group]  = panel->group_first;
    if (cursor != panel->group_cursor) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (panel->confirm_timer == 0) {
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 6));
            state_counter       = &D_80148651;
            panel->group        = 0;
            panel->group_cursor = 0xFF;
            panel->drawn_cursor = 0xFF;
            *state_counter      = *state_counter - 7;
            panel->group_first  = s_ChoiceMenuValues[0];
        }
    }
}
