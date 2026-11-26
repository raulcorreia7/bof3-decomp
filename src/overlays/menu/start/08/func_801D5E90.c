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
    u8             clut;
    clut  = g_WindowClut;
    panel = &g_UiPanelTasks[14];
    /* FAKE: hides the constant so the panel base stays in a saved register from the prologue. */
    FAKE_OPAQUE(panel);
    Menu_DrawClutStrip(clut);
    g_UiPanelTasks[21].active                                 = 1;
    D_80148628                                                = g_UiPanelTasks[14].pos.vx + 7;
    D_8014862A                                                = g_UiPanelTasks[14].pos.vy + ((g_UiPanelTasks[14].unk_0B - g_UiPanelTasks[14].unk_0A) * 13 + 0x1A);
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(g_UiPanelTasks[14].unk_08, g_UiPanelTasks[14].flags);
    buttons                                                   = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    func_801D6FBC();
    old = g_UiPanelTasks[14].unk_0B;
    if (buttons & PADLup) {
        if (old != 0) {
            g_UiPanelTasks[14].unk_0B = old - 1;
        }
        if (g_UiPanelTasks[14].unk_0B < g_UiPanelTasks[14].unk_0A) {
            g_UiPanelTasks[14].u.addr.unk_10 = 240;
        }
    } else if (buttons & PADLdown) {
        if (old < 127) {
            g_UiPanelTasks[14].unk_0B = old + 1;
        }
        if (g_UiPanelTasks[14].unk_0B >= g_UiPanelTasks[14].unk_0A + 9) {
            g_UiPanelTasks[14].u.addr.unk_10 = 16;
        }
    } else if (buttons & PADL1) {
        first_row = g_UiPanelTasks[14].unk_0A;
        if (first_row == 0) {
            g_UiPanelTasks[14].unk_0B = 0;
        } else if (first_row < 9) {
            g_UiPanelTasks[14].unk_0B = old - first_row;
            g_UiPanelTasks[14].unk_0A = 0;
        } else {
            g_UiPanelTasks[14].unk_0B = old - 9;
            g_UiPanelTasks[14].unk_0A = first_row - 9;
        }
    } else if (buttons & PADR1) {
        last_row = g_UiPanelTasks[14].unk_0A;
        if (last_row == 119) {
            g_UiPanelTasks[14].unk_0B = 127;
        } else if (old >= 111) {
            next                      = old + 119;
            g_UiPanelTasks[14].unk_0B = next - last_row;
            g_UiPanelTasks[14].unk_0A = 119;
        } else {
            g_UiPanelTasks[14].unk_0B = old + 9;
            g_UiPanelTasks[14].unk_0A = last_row + 9;
        }
    }
    if (g_UiPanelTasks[13].unk_0A < 4) {
        s_SkillOrderGroups[g_UiPanelTasks[13].unk_0C][g_UiPanelTasks[13].unk_0A] = g_UiPanelTasks[14].unk_0A;
        s_SkillOrderTypes[g_UiPanelTasks[13].unk_0C][g_UiPanelTasks[13].unk_0A]  = g_UiPanelTasks[14].unk_0B;
    } else {
        s_SkillOrderGroups[g_UiPanelTasks[13].unk_0C][4] = s_SkillOrderGroups[g_UiPanelTasks[13].unk_0C][5] = g_UiPanelTasks[14].unk_0A;
        s_SkillOrderTypes[g_UiPanelTasks[13].unk_0C][4] = s_SkillOrderTypes[g_UiPanelTasks[13].unk_0C][5] = g_UiPanelTasks[14].unk_0B;
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
                g_UiPanelTasks[14].unk_0B = GAME_NONE;
                g_MenuStep.sub_step -= 1;
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            }
        } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            g_UiPanelTasks[14].unk_0B                            = GAME_NONE;
            g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
            g_MenuStep.sub_step -= 1;
        }
    }
}
#else
INCLUDE_ASM(func_801D5E90);
#endif
