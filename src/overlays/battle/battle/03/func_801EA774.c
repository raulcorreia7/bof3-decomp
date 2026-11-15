#include "battle_03.h"

MATCH void func_801EA774(void) {
    MenuPanelTask* panel = g_MenuCurrentPanel;
    s16            state = panel->pos.y;

    if (state == -0x16) {
        u8* gate = &g_Battle.outcome.event_flags;

        *gate &= ~D_801EB4DC->event_type;
        Menu_ClearPanel();
    } else {
        panel->pos.y = state - 8;
    }
}
