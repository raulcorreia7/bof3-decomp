#include "battle_15.h"

MATCH void func_800B0410(void) {
    BattlePanelTask* panel;

    func_800B0498();
    panel = BATTLE_PANEL_TASK;
    if (panel->selection.mode == 0) {
        if (panel->x.signed_value < 0x142) {
            panel->x.signed_value += 0x20;
            return;
        }
        UI_PanelClear();
        return;
    }
    if (panel->x.signed_value < -0xBD) {
        UI_PanelClear();
        return;
    }
    panel->x.signed_value -= 0x20;
}
