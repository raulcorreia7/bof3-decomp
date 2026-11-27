#include "area056_13.h"

/* Twin of func_801F2C04 in this image (scene flag 12 instead of 8);
 * consolidate the bodies in the polish pass. */
MATCH void func_801F2EA8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        D_80145E91[0] = 2;
        D_80145E92[0] = 7;
        D_80145E93[0] = 0;
        Area_CellSetPalette(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer);
    }
    if (g_UIMessageChoice == 1) {
        SYS_SetFlag(D_80144EA0, 12);
    }
    if (g_UIMessageChoice != 2) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x08));
    }
}
