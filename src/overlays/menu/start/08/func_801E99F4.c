#include "start_08.h"

MATCH void func_801E99F4(void) {
    g_MenuStartPanel7Steps[g_UiPanelCurrent->state]();
    func_801DC150(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, g_CharSlot[g_PartyFieldOrder[g_UiPanelCurrent->unk_0A]], 0);
}
