#include "start_08.h"

void Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index);

MATCH void func_801E96CC(void) {
    D_801ED3E0[g_MenuCurrentPanel->state]();
    Menu_DrawStatPanel(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                       g_CharSlot[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0A]]);
}
