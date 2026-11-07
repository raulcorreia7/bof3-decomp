#include "start_08.h"

void func_801E7608(void);

MATCH void func_801E441C(void) {
    func_801E7608();
    func_801E6D88(0);
    if (g_UiWindowChannel & FRONTEND_FLAG_CONFIRM) {
        if ((D_801ED86C != 0) && (g_InputPressed & (PADLup | PADLdown))) {
            D_801ED7EC ^= 1;
            SND_PlayCue(EMI_CUE_ID(1, 1));
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
        if ((g_InputPressed & g_InputMasks[INPUT_SLOT_CONFIRM]) || (g_InputPressed & PADstart)) {
            UI_SetMode(UI_MODE_FADE_OUT);
            g_MenuStartStep += 1;
            SND_PlayCue(EMI_CUE_ID(1, 5));
        }
    }
}
