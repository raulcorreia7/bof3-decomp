#include "start_08.h"

MATCH void func_801E5320(void) {
    u32  prev;
    u8   prev_byte;
    u16* pad;
    u8   count;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 21, 0xAA);
    func_801E14A8(0x62, 0x4C, D_801ED870, g_SaveCardPort, 0);
    prev      = g_SaveCardPort;
    prev_byte = prev;
    if ((g_InputPressed & (PADLup | PADLdown)) != 0) {
        if (prev == D_801ED7F4) {
            g_SaveCardPort = D_801ED7F8;
        } else {
            g_SaveCardPort = D_801ED7F4;
        }
        if (prev_byte != g_SaveCardPort) {
            SND_PlayCue(EMI_CUE_ID(1, 1));
        }
    }
    pad = &g_InputPressed;
    if ((*pad & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 4));
        g_MenuStartTimer      = 2;
        D_801ED7FC            = 5;
        count                 = g_MenuStartStep;
        g_MenuStartStep       = 0xE;
        g_MenuStartReturnStep = count + 1;
    } else if ((*pad & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        g_MenuStartStep     = 0;
        g_GameEntrySubstate = 1;
    }
}
