#include "battle_03.h"

MATCH void func_801DE754(void) {
    volatile u8*     gate;
    BattleEventSlot* panel;
    BattleEventSlot* panel2;
    u16              half;
    ScratchPad*      sp;

    panel = D_801EB4DC;
    gate  = &g_BattleEventFlags;
    *gate |= panel->unk_01;
    half = panel->unk_08;
    if (half != 0xFFu) {
        panel->unk_08 = half - 1;
    }
    panel2 = D_801EB4DC;
    if (panel2->unk_08 == 0u) {
        panel2->unk_00 = 0;
        if (func_801DE858(4) != 0u) {
            g_MenuPanelTasks[0].state = 2;
        }
    } else {
        sp                    = SPAD(0u);
        D_8014833A[0].kind_00 = sp->view.battle.state_00;
    }
}
