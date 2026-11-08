#include "battle_03.h"

MATCH void func_801D2480(void) {
    u8 value;

    value = g_Battle.panel_widths[g_Battle.panel_slot];
    if (value < 8u) {
        g_Battle.panel_widths[g_Battle.panel_slot] = value + 4;
    } else {
        g_Battle.phase.step     = 2;
        g_Battle.phase.sub_step = 0;
    }
}
