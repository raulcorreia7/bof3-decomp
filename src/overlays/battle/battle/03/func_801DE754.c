#include "battle_03.h"

MATCH void func_801DE754(void) {
    volatile u8*     gate;
    BattleEventSlot* panel;
    BattleEventSlot* panel2;
    u16              half;
    ScratchPad*      sp;

    panel = D_801EB4DC;
    gate  = &g_Battle.outcome.event_flags;
    *gate |= panel->event_type;
    half = panel->timer;
    if (half != 0xFFu) {
        panel->timer = half - 1;
    }
    panel2 = D_801EB4DC;
    if (panel2->timer == 0u) {
        panel2->active = 0;
        if (func_801DE858(4) != 0u) {
            g_MenuPanelTasks[0].state = 2;
        }
    } else {
        sp                    = SPAD(0u);
        D_8014833A[0].kind_00 = sp->view.battle.state_00;
    }
}
