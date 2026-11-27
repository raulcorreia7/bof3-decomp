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

    Menu_DrawClutStrip(g_WindowClut);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id =
        Item_GetDescription(g_UIPanelTasks[13].unk_0A, g_ItemCategoryIds[g_UIPanelTasks[13].unk_0A][g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]);
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vx = (u16)g_UIPanelTasks[MENU_START_PANEL_ITEMS].pos.vx + 7;
    span                                           = (g_UIPanelTasks[13].unk_0C - g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) * 0xD + 0x1A;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vy = (u16)g_UIPanelTasks[MENU_START_PANEL_ITEMS].pos.vy + span;
    panel                                          = &D_80148504;
    pressed                                        = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown | PADL1 | PADR1));
    cursor                                         = g_UIPanelTasks[13].unk_0C;
    if (pressed & PADLup) {
        if (cursor != 0) {
            g_UIPanelTasks[13].unk_0C = cursor - 1;
        }
        if ((u32)g_UIPanelTasks[13].unk_0C < (u32)g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) {
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0xF0;
        }
    } else if (pressed & PADLdown) {
        if ((u32)cursor < 0x1FU) {
            g_UIPanelTasks[13].unk_0C = cursor + 1;
        }
        if (g_UIPanelTasks[13].unk_0C >= g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9) {
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0x10;
        }
    } else if (pressed & PADL1) {
        if ((g_UIPanelTasks[13].unk_0B & BYTE_MASK) == 0) {
            g_UIPanelTasks[13].unk_0C = 0;
        } else if ((u32)(g_UIPanelTasks[13].unk_0B & BYTE_MASK) < 9U) {
            g_UIPanelTasks[13].unk_0C                     = cursor - g_UIPanelTasks[13].unk_0B;
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0;
        } else {
            g_UIPanelTasks[13].unk_0C = cursor - 9;
            g_UIPanelTasks[13].unk_0B = g_UIPanelTasks[13].unk_0B - 9;
        }
    } else if (pressed & PADR1) {
        page_start        = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
        page_start_masked = page_start & BYTE_MASK;
        if (page_start_masked == 0x17) {
            g_UIPanelTasks[13].unk_0C = 0x1F;
        } else if (page_start_masked >= 0xF) {
            scrolled                  = cursor + 0x17;
            g_UIPanelTasks[13].unk_0C = scrolled - page_start;
            g_UIPanelTasks[13].unk_0B = 0x17;
        } else {
            g_UIPanelTasks[13].unk_0C = cursor + 9;
            g_UIPanelTasks[13].unk_0B = page_start + 9;
        }
    }
    s_ChoiceMenuCursors[panel->group] = panel->group_cursor;
    s_ChoiceMenuValues[panel->group]  = panel->group_first;
    if (cursor != panel->group_cursor) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (panel->confirm_timer == 0) {
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            state_counter       = &D_80148651;
            panel->group        = 0;
            panel->group_cursor = 0xFF;
            panel->drawn_cursor = 0xFF;
            *state_counter      = *state_counter - 7;
            panel->group_first  = s_ChoiceMenuValues[0];
        }
    }
}
