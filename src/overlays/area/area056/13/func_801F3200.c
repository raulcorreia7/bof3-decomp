#include "area056_13.h"

/* The cell's palette step: clears the pending message, plays the change sound, and applies the
 * cell palette once the counter byte has run to 0x7F. */
MATCH void func_801F3200(void) {
    u8* type;

    MESSAGE_REQUEST_CLEAR();
    type = D_80145E92;
    if (g_UIMessageChoice != 0) {
        return;
    }

    SND_SEPlay(0x208);
    if ((D_80144EA1 & 0x7F) != 0x7F) {
        return;
    }

    D_80145E91[0] = 2;
    *type         = 7;
    D_80145E93[0] = 0;
    Area_CellSetPalette(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer);
}
