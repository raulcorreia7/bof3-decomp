#include "area056_13.h"

/* The func_801F2C04 request entry with the palette and flag guards
 * swapped (scene flag 11). */
MATCH void func_801F2DFC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 1) {
        D_80145E91[0] = 2;
        D_80145E92[0] = 7;
        D_80145E93[0] = 0;
        Area_SetCellPalette(D_80145EC6, D_80145ECA);
    }
    if (g_MessageChoice == 0) {
        SYS_SetFlag(D_80144EA0, 11);
    }
    if (g_MessageChoice != 2) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x08));
    }
}
