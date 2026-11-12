#include "battle_03.h"

MATCH void func_801D22E8(void) {
    u8 value;

    value = g_Battle.panel_widths[g_Battle.panel_slot];
    if (value != 0) {
        g_Battle.panel_widths[g_Battle.panel_slot] = value - 2;
    } else {
        g_Battle.phase.sub_step += 1;
    }
    func_801D8450(g_Battle.panel_slot);
    func_801D750C(D_80148358, D_8014835A);
    Battle_DrawPanelRows(D_8014837C, D_8014837E);
}
