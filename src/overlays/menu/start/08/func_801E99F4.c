#include "start_08.h"

MATCH void func_801E99F4(void) {
    D_801ED408[g_MenuCurrentPanel->state]();
    func_801DC150(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                  g_CharSlot[D_80144F5A[g_MenuCurrentPanel->unk_0A]], 0);
}
