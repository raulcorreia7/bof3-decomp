#include "battle_03.h"

MATCH void func_801EA774(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;
    s16            state = panel->pos.y;

    if (state == -0x16) {
        u8* gate = &g_BattleOutcome.event_flags;

        *gate &= ~D_801EB4DC->unk_01;
        func_80158E20();
    } else {
        panel->pos.y = state - 8;
    }
}
