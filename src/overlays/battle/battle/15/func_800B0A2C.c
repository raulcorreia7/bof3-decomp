#include "battle_15.h"

MATCH void func_800B0A2C(void) {
    BattlePanelTask* panel;
    u8               cursor;

    panel                 = BATTLE_PANEL_TASK;
    panel->x.signed_value = 0x5A;
    cursor                = panel->state;
    panel->y.signed_value = -0x17;
    panel->state          = cursor + 1;
}
