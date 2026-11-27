#include "area056_13.h"

/* The func_801F2C04 request entry with the palette and flag guards
 * swapped (scene flag 13). */
MATCH void func_801F2F50(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 1) {
        D_80145E91[0] = 2;
        D_80145E92[0] = 7;
        D_80145E93[0] = 0;
        Area_CellSetPalette(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer);
    }
    if (g_UIMessageChoice == 0) {
        SYS_SetFlag(D_80144EA0, 13);
    }
    if (g_UIMessageChoice != 2) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x08));
    }
}
