#include "shop_00.h"

MATCH void func_801D4A3C(void) {
    u32  prev;
    u8   prev_byte;
    u16* pad;
    u8*  mode;
    u8   count;

    MENU_DRAW_HEADER();
    WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0x98);
    func_801DDFB0(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    prev      = g_SaveCardPort;
    prev_byte = prev;
    if ((g_InputPressed & (PADLup | PADLdown)) != 0) {
        if (prev == D_801E6088) {
            g_SaveCardPort = D_801E608C;
        } else {
            g_SaveCardPort = D_801E6088;
        }
        if (prev_byte != g_SaveCardPort) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        }
    }
    pad = &g_InputPressed;
    if ((*pad & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        D_801E60EC = SAVE_WAIT_SCAN;
        mode       = &g_MenuStep.state;
        count      = *mode;
        *mode      = 0x13;
        D_80148654 = 2;
        D_801E6094 = count + 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
    }
    if ((*pad & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801E6080       = 1;
        g_MenuStep.state = 6;
    }
}
