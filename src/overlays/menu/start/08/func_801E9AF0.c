#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

MATCH void func_801E9AF0(void) {
    g_MenuStartPanel8Steps[g_UiPanelCurrent->state]();
    func_801DC150(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, g_CharSlot[g_PartyFieldOrder[g_UiPanelCurrent->unk_0A]], 1);
}
