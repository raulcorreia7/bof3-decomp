#include "shop_00.h"

MATCH void func_801D4A3C(void) {
    u32  prev;
    u8   prev_byte;
    u16* pad;
    u8*  mode;
    u8   count;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 22, 0x98);
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
            SND_PlayCue(EMI_CUE_ID(1, 1));
        }
    }
    pad = &g_InputPressed;
    if ((*pad & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0) {
        D_801E60EC = SAVE_WAIT_SCAN;
        mode       = &D_80148652;
        count      = *mode;
        *mode      = 0x13;
        D_80148654 = 2;
        D_801E6094 = count + 1;
        SND_PlayCue(EMI_CUE_ID(1, 4));
    }
    if ((*pad & g_InputMasks[INPUT_SLOT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_801E6080 = 1;
        D_80148652 = 6;
    }
}
