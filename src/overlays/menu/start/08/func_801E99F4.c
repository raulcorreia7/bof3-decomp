#include "start_08.h"

MATCH void func_801E99F4(void) {
    D_801ED408[g_MenuPanelTaskCurrent->state]();
    func_801DC150(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y,
                  g_CharSlot[D_80144F5A[g_MenuPanelTaskCurrent->unk_0A]], 0);
}
