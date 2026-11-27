#include "battle_03.h"

/* func_801EA774 */
MATCH void Battle_SlideOutEventPanel(void) {
    MenuPanelTask* panel = g_UIPanelCurrent;
    s16            state = panel->pos.vy;

    if (state == -0x16) {
        u8* gate = &g_Battle.outcome.event_flags;

        *gate &= ~D_801EB4DC->event_type;
        UI_PanelClear();
    } else {
        panel->pos.vy = state - 8;
    }
}
