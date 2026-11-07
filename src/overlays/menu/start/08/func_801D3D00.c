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

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[11].unk_10 = Item_GetDescription(D_8014850E, D_801C893C[D_8014850E][g_MenuPanelTasks[13].unk_0C]);
    g_MenuPanelTasks[21].active = 1;
    g_MenuPanelTasks[14].unk_0C = 0;
    g_MenuPanelTasks[21].pos.x  = (u16)g_MenuPanelTasks[13].pos.x + 7;
    span                        = (D_80148510 - g_MenuPanelTasks[13].unk_0B) * 0xD + 0x1A;
    g_MenuPanelTasks[21].pos.y  = (u16)g_MenuPanelTasks[13].pos.y + span;
    panel                       = &D_80148504;
    pressed                     = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown | PADL1 | PADR1));
    cursor                      = D_80148510;
    if (pressed & PADLup) {
        if (cursor != 0) {
            D_80148510 = cursor - 1;
        }
        if ((u32)D_80148510 < (u32)g_MenuPanelTasks[13].unk_0B) {
            g_MenuPanelTasks[13].unk_12 = 0xF0;
        }
    } else if (pressed & PADLdown) {
        if ((u32)cursor < 0x7FU) {
            D_80148510 = cursor + 1;
        }
        if (D_80148510 >= g_MenuPanelTasks[13].unk_0B + 9) {
            g_MenuPanelTasks[13].unk_12 = 0x10;
        }
    } else if (pressed & 4) {
        if ((D_8014850F & BYTE_MASK) == 0) {
            D_80148510 = 0;
        } else if ((u32)(D_8014850F & BYTE_MASK) < 9U) {
            D_80148510                  = cursor - D_8014850F;
            g_MenuPanelTasks[13].unk_0B = 0;
        } else {
            D_80148510 = cursor - 9;
            D_8014850F = D_8014850F - 9;
        }
    } else if (pressed & 8) {
        page_start        = g_MenuPanelTasks[13].unk_0B;
        page_start_masked = page_start & BYTE_MASK;
        if (page_start_masked == 0x77) {
            D_80148510 = 0x7F;
        } else if (page_start_masked >= 0x6F) {
            scrolled   = cursor + 0x77;
            D_80148510 = scrolled - page_start;
            D_8014850F = 0x77;
        } else {
            D_80148510 = cursor + 9;
            D_8014850F = page_start + 9;
        }
    }
    s_ChoiceMenuCursors[panel->group] = panel->group_cursor;
    s_ChoiceMenuValues[panel->group]  = panel->group_first;
    if (cursor != panel->group_cursor) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (panel->confirm_gate == 0) {
        if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (panel->drawn_cursor == GAME_NONE) {
                SND_PlayCue(EMI_CUE_ID(1, 3));
                if (D_801C893C[panel->group][panel->group_cursor] != 0) {
                    panel->drawn_cursor = panel->group_cursor;
                    return;
                }
                SND_PlayCue(EMI_CUE_ID(1, 7));
                return;
            }
            SND_PlayCue(EMI_CUE_ID(1, 3));
            Menu_SwapBytes(&D_801C893C[panel->group][panel->drawn_cursor],
                           &D_801C893C[panel->group][panel->group_cursor]);
            Menu_SwapBytes(&D_801C8950[panel->group][panel->drawn_cursor],
                           &D_801C8950[panel->group][panel->group_cursor]);
            panel->drawn_cursor = 0xFF;
        } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            if (panel->drawn_cursor == GAME_NONE) {
                state_counter  = &D_80148652;
                *state_counter = *state_counter - 1;
                return;
            }
            panel->drawn_cursor = 0xFF;
        }
    }
}
