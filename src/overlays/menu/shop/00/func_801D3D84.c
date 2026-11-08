#include "shop_00.h"

MATCH void func_801D3D84(void) {
    u8   mode;
    u8   prev;
    u8*  rate;
    u32* gold;

    func_801D6D6C(0x6E, 0x4C);
    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        WinDrawCueText(28, 22, 0xA1);
        Menu_DrawZennyWindow(0x62, 0x28, 0, g_Zenny);
    }
    prev = D_801E60F0;
    if (g_InputPressed & PADLup) {
        mode       = prev - 1;
        D_801E60F0 = mode;
        if ((s8)mode < 0) {
            D_801E60F0 = 2;
        }
    } else if (g_InputPressed & PADLdown) {
        mode       = prev + 1;
        D_801E60F0 = mode;
        if (mode >= 3) {
            D_801E60F0 = 0;
        }
    }
    if (prev != D_801E60F0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        mode       = D_801E60F0;
        D_80148654 = 0;
        D_801E60F4 = 0;
        if (mode == 0) {
            rate = &D_80148699;
            gold = &g_Zenny;
            if (*gold >= *rate * 10) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                *gold -= *rate * 10;
                D_80148652 += 2;
                return;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            D_80148652 += 1;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        D_80148652 += 2;
        return;
    }
    if ((g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) == 0) {
        return;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    D_80148654 = 0;
    D_801E60F4 = 1;
    D_80148652 += 2;
}
