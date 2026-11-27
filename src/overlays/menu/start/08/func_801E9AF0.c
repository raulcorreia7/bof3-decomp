#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

MATCH void func_801E9AF0(void) {
    g_MenuStartPanel8Steps[g_UIPanelCurrent->state]();
    func_801DC150(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_CharSlot[g_PartyFieldOrder[g_UIPanelCurrent->unk_0A]], 1);
}
