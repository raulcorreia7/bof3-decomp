#include "start_08.h"

void Menu_DrawBackdrop(void);

MATCH void func_801E441C(void) {
    Menu_DrawBackdrop();
    func_801E6D88(0);
    if (g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) {
        if ((D_801ED86C != 0) && (g_PadStates[0].pressed & (PADLup | PADLdown))) {
            D_801ED7EC ^= 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        }
        if (D_801ED7EC != 0) {
            D_801ED864 += 8;
            if (D_801ED864 >= 0x81) {
                D_801ED864 = 0x80;
            }
            D_801ED868 -= 8;
            CLAMP_MIN(D_801ED868, 0x40);
        } else {
            D_801ED864 -= 8;
            CLAMP_MIN(D_801ED864, 0x40);
            D_801ED868 += 8;
            if (D_801ED868 >= 0x81) {
                D_801ED868 = 0x80;
            }
        }
        if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) || (g_PadStates[0].pressed & PADstart)) {
            UI_ModeSet(UI_MODE_FADE_OUT);
            g_MenuCampStep += 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 5));
        }
    }
}
