#include "start_08.h"

/* Runs the skill-order type list: scrolls panel 14 by the pad, stores the pick in the order tables, and confirms or cancels. */
MATCH void func_801D5E90(void) {
    MenuPanelTask* panel;
    MenuPanelTask* frame;
    s32            buttons;
    u16            pad;
    u8             old;
    u8             first_row;
    u8             last_row;
    u8             next;
    u8             clut;
    clut  = g_WindowClut;
    panel = &g_UIPanelTasks[14];
    Menu_DrawClutStrip(clut);
    frame                                                     = panel + 7;
    frame->active                                             = 1;
    D_80148628                                                = g_UIPanelTasks[14].pos.vx + 7;
    D_8014862A                                                = g_UIPanelTasks[14].pos.vy + ((g_UIPanelTasks[14].unk_0B - g_UIPanelTasks[14].unk_0A) * 13 + 0x1A);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(g_UIPanelTasks[14].unk_08, g_UIPanelTasks[14].flags);
    panel                                                     = frame;
    panel -= 7;
    buttons = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    func_801D6FBC();
    old = D_80148533;
    if (buttons & PADLup) {
        if (old != 0) {
            D_80148533 = old - 1;
        }
        if (D_80148533 < D_80148532) {
            g_UIPanelTasks[14].u.addr.unk_10 = 240;
        }
    } else if (buttons & PADLdown) {
        if (old < 127) {
            D_80148533 = old + 1;
        }
        if (D_80148533 >= D_80148532 + 9) {
            g_UIPanelTasks[14].u.addr.unk_10 = 16;
        }
    } else if (buttons & PADL1) {
        first_row = D_80148532;
        if (first_row == 0) {
            D_80148533 = 0;
        } else if (first_row < 9) {
            D_80148533 = old - first_row;
            D_80148532 = 0;
        } else {
            D_80148533 = old - 9;
            D_80148532 = first_row - 9;
        }
    } else if (buttons & PADR1) {
        last_row = D_80148532;
        if (last_row == 119) {
            D_80148533 = 127;
        } else if (old >= 111) {
            next       = old + 119;
            D_80148533 = next - last_row;
            D_80148532 = 119;
        } else {
            D_80148533 = old + 9;
            D_80148532 = last_row + 9;
        }
    }
    if (g_UIPanelTasks[13].unk_0A < 4) {
        s_SkillOrderGroups[g_UIPanelTasks[13].unk_0C][g_UIPanelTasks[13].unk_0A] = D_80148532;
        s_SkillOrderTypes[g_UIPanelTasks[13].unk_0C][g_UIPanelTasks[13].unk_0A]  = D_80148533;
    } else {
        s_SkillOrderGroups[g_UIPanelTasks[13].unk_0C][4] = s_SkillOrderGroups[g_UIPanelTasks[13].unk_0C][5] = D_80148532;
        s_SkillOrderTypes[g_UIPanelTasks[13].unk_0C][4] = s_SkillOrderTypes[g_UIPanelTasks[13].unk_0C][5] = D_80148533;
    }
    if (old != (*panel).unk_0B) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if ((s16)(*panel).u.addr.unk_10 == 0) {
        pad = g_PadStates[0].pressed;
        if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if ((*panel).flags != 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                func_801D6E6C();
                g_UIPanelTasks[14].unk_0B = GAME_NONE;
                g_MenuStep.sub_step -= 1;
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            }
        } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            g_UIPanelTasks[14].unk_0B                            = GAME_NONE;
            g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
            g_MenuStep.sub_step -= 1;
        }
    }
}
