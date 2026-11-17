#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D5E90(void) {
    MenuPanelTask* panel;
    s32            buttons;
    u16            pad;
    u8             old;
    u8             first_row;
    u8             last_row;
    u8             next;
    u8             group;
    u8*            cursor;

    panel = &g_MenuPanelTasks[14];
    Menu_DrawClutStrip(D_80144953);
    D_80148624                                                  = 1;
    D_80148628                                                  = g_MenuPanelTasks[14].pos.x + 7;
    D_8014862A                                                  = g_MenuPanelTasks[14].pos.y + ((g_MenuPanelTasks[14].unk_0B - g_MenuPanelTasks[14].unk_0A) * 13 + 0x1A);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(g_MenuPanelTasks[14].unk_08, g_MenuPanelTasks[14].flags);
    buttons                                                     = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    func_801D6FBC();
    old = g_MenuPanelTasks[14].unk_0B;
    if (buttons & PADLup) {
        if (old != 0) {
            g_MenuPanelTasks[14].unk_0B = old - 1;
        }
        if (g_MenuPanelTasks[14].unk_0B < g_MenuPanelTasks[14].unk_0A) {
            g_MenuPanelTasks[14].u.addr.unk_10 = 240;
        }
    } else if (buttons & PADLdown) {
        if (old < 127) {
            g_MenuPanelTasks[14].unk_0B = old + 1;
        }
        if (g_MenuPanelTasks[14].unk_0B >= g_MenuPanelTasks[14].unk_0A + 9) {
            g_MenuPanelTasks[14].u.addr.unk_10 = 16;
        }
    } else if (buttons & PADL1) {
        first_row = g_MenuPanelTasks[14].unk_0A;
        if (first_row == 0) {
            g_MenuPanelTasks[14].unk_0B = 0;
        } else if (first_row < 9) {
            g_MenuPanelTasks[14].unk_0B = old - first_row;
            g_MenuPanelTasks[14].unk_0A = 0;
        } else {
            g_MenuPanelTasks[14].unk_0B = old - 9;
            g_MenuPanelTasks[14].unk_0A = first_row - 9;
        }
    } else if (buttons & PADR1) {
        last_row = g_MenuPanelTasks[14].unk_0A;
        if (last_row == 119) {
            g_MenuPanelTasks[14].unk_0B = 127;
        } else if (old >= 111) {
            next                        = old + 119;
            g_MenuPanelTasks[14].unk_0B = next - last_row;
            g_MenuPanelTasks[14].unk_0A = 119;
        } else {
            g_MenuPanelTasks[14].unk_0B = old + 9;
            g_MenuPanelTasks[14].unk_0A = last_row + 9;
        }
    }
    group  = D_8014850E;
    cursor = &g_MenuPanelTasks[14].unk_0B;
    if (group < 4) {
        s_SkillOrderGroups[D_80148510][group] = g_MenuPanelTasks[14].unk_0A;
        s_SkillOrderKinds[D_80148510][group]  = g_MenuPanelTasks[14].unk_0B;
    } else {
        *(&D_801ED8BD + D_80148510 * 6) = g_MenuPanelTasks[14].unk_0A;
        *(&D_801ED8BC + D_80148510 * 6) = g_MenuPanelTasks[14].unk_0A;
        *(&D_801ED8D5 + D_80148510 * 6) = g_MenuPanelTasks[14].unk_0B;
        *(&D_801ED8D4 + D_80148510 * 6) = g_MenuPanelTasks[14].unk_0B;
    }
    if (old != *cursor) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if ((s16)g_MenuPanelTasks[14].u.addr.unk_10 == 0) {
        pad = g_InputPressed;
        if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (g_MenuPanelTasks[14].flags != 0) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 4));
                func_801D6E6C();
                g_MenuPanelTasks[14].unk_0B = GAME_NONE;
                g_MenuStep.sub_step -= 1;
            } else {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 7));
            }
        } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 6));
            g_MenuPanelTasks[14].unk_0B                            = GAME_NONE;
            g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
            g_MenuStep.sub_step -= 1;
        }
    }
}
#else
INCLUDE_ASM(func_801D5E90);
#endif
