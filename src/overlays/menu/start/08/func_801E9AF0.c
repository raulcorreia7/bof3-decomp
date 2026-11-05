#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

MATCH void func_801E9AF0(void) {
    D_801ED414[g_MenuPanelTaskCurrent->state]();
    func_801DC150((s16)g_MenuPanelTaskCurrent->x, (s16)g_MenuPanelTaskCurrent->y,
                  g_CharSlot[D_80144F5A[g_MenuPanelTaskCurrent->unk_0A]], 1);
}
