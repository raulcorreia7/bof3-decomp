#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

MATCH void func_801E9AF0(void) {
    g_MenuStartPanel8StateFuncs[g_MenuCurrentPanel->state]();
    func_801DC150(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_CharSlot[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0A]], 1);
}
