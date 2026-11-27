#include "start_08.h"

MATCH void func_801E99F4(void) {
    g_MenuStartPanel7Steps[g_UIPanelCurrent->state]();
    func_801DC150(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_CharSlot[g_PartyFieldOrder[g_UIPanelCurrent->unk_0A]], 0);
}
