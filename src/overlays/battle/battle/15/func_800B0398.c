#include "battle_15.h"

MATCH void func_800B0398(void) {
    BattlePanelTask* panel;

    func_800B0498();
    panel = BATTLE_PANEL_TASK;
    if (panel->selection.mode == 0) {
        if (panel->x.signed_half < 0x43) {
            panel->x.signed_half = 0x42;
        } else {
            panel->x.signed_half = panel->x.signed_half - 0x20;
        }
    } else {
        if (panel->x.signed_half < 0x42) {
            panel->x.signed_half = panel->x.signed_half + 0x20;
        } else {
            panel->x.signed_half = 0x42;
        }
    }
}
