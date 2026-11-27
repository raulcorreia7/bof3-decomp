#include "shop_00.h"

MATCH void func_801E2150(void) {
    s32 buttons;
    u16 pad;
    u8  next;
    u8  row;

    D_80148340                = 0x32;
    g_UiPanelTasks[21].active = 1;
    g_UiPanelTasks[8].unk_0A  = 0;
    g_UiPanelTasks[21].pos.vx = g_UiPanelTasks[1].pos.vx + 4;
    g_UiPanelTasks[21].pos.vy = g_UiPanelTasks[1].pos.vy + (g_UiPanelTasks[1].unk_0B - g_UiPanelTasks[1].unk_0A) * 0xD + 0x1A;
    buttons                   = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    row                       = g_UiPanelTasks[1].unk_0B;
    if (buttons & PADLup) {
        if (row != 0) {
            g_UiPanelTasks[1].unk_0B = row - 1;
        }
        if (g_UiPanelTasks[1].unk_0B < g_UiPanelTasks[1].unk_0A) {
            g_UiPanelTasks[1].unk_08 = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (row < 16) {
            g_UiPanelTasks[1].unk_0B = row + 1;
        }
        if (g_UiPanelTasks[1].unk_0B >= g_UiPanelTasks[1].unk_0A + 9) {
            g_UiPanelTasks[1].unk_08 = 0x10;
        }
    } else if (buttons & PADL1) {
        if (g_UiPanelTasks[1].unk_0A == 0) {
            g_UiPanelTasks[1].unk_0B = 0;
        } else if (g_UiPanelTasks[1].unk_0A < 9) {
            g_UiPanelTasks[1].unk_0B -= g_UiPanelTasks[1].unk_0A;
            g_UiPanelTasks[1].unk_0A = 0;
        } else {
            g_UiPanelTasks[1].unk_0B -= 9;
            g_UiPanelTasks[1].unk_0A -= 9;
        }
    } else if (buttons & PADR1) {
        if (g_UiPanelTasks[1].unk_0A == 8) {
            g_UiPanelTasks[1].unk_0B = 0x10;
        } else {
            next                     = row + 8;
            g_UiPanelTasks[1].unk_0B = next - g_UiPanelTasks[1].unk_0A;
            g_UiPanelTasks[1].unk_0A = 8;
        }
    }
    if (row != g_UiPanelTasks[1].unk_0B) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (g_UiPanelTasks[1].unk_08 == 0) {
        pad = g_PadStates[0].pressed;
        if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (g_UiPanelTasks[1].flags != GAME_NONE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                func_801E2724();
                g_UiPanelTasks[1].state   = 3;
                g_UiPanelTasks[21].active = 0;
                D_80148654                = 8;
                D_80148652 += 1;
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            }
        } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            g_UiPanelTasks[0].state   = 1;
            g_UiPanelTasks[1].state   = 1;
            g_UiPanelTasks[21].active = 0;
            D_80148654                = 0xA;
            D_80148652                = 0;
            D_80148651 += 1;
        }
    }
}
