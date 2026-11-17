#include "battle_15.h"

MATCH void func_800B0AB0(void) {
    s16 value;

    value                             = BATTLE_PANEL_TASK->y.signed_value;
    BATTLE_PANEL_TASK->y.signed_value = value < -0x16 ? -0x17 : value - 0x10;
    func_800B0B0C(BATTLE_PANEL_TASK->x.signed_value, BATTLE_PANEL_TASK->y.signed_value);
}
