#include "area056_13.h"

/* Twin of func_801F2C04 in this image (scene flag 10 instead of 8);
 * consolidate the bodies in the polish pass. */
MATCH void func_801F2D54(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        D_80145E91[0] = 2;
        D_80145E92[0] = 7;
        D_80145E93[0] = 0;
        Area_SetCellPalette(D_80145EC6, D_80145ECA);
    }
    if (D_801490C7 == 1) {
        SYS_SetFlag(D_80144EA0, 10);
    }
    if (D_801490C7 != 2) {
        SND_PlayCue(0x208);
    }
}
