#include "start_08.h"

void Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index);

MATCH void func_801E96CC(void) {
    D_801ED3E0[g_MenuPanelTaskCurrent->state]();
    Menu_DrawStatPanel(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y,
                       g_CharSlot[D_80144F5A[g_MenuPanelTaskCurrent->unk_0A]]);
}
