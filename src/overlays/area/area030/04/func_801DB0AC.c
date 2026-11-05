#include "area030_04.h"

/* Clears the AREA030 slot's timer word when the current sub-state's
 * mask bit is set in the world state word, and fills it otherwise. */
MATCH void func_801DB0AC(void) {
    if ((g_FrameCount & (3 >> D_801E320C->unk_03)) == 0) {
        D_801468A4[D_801E3208].state = -1;
    } else {
        D_801468A4[D_801E3208].state = 0;
    }
}
