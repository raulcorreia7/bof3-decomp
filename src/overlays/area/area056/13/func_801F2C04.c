#include "area056_13.h"

MATCH s32 func_801F2C04(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        D_80145E91[0] = 2;
        D_80145E92[0] = 7;
        D_80145E93[0] = 0;
        Area_SetCellPalette(D_80145EC6, D_80145ECA);
    }
    if (g_MessageChoice == 1) {
        SYS_SetFlag(D_80144EA0, 8);
    }
    if (g_MessageChoice != 2) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x08));
    }
}
