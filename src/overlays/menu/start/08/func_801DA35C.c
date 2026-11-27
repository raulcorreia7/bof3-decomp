#include "start_08.h"

MATCH void func_801DA35C(void) {
    u8             index;
    u8*            panel_data;
    u8             remaining;
    MenuPanelTask* panel;
    u8*            timer;
    u8*            state_counter;

    panel_data = &g_WindowClut;
    Menu_DrawClutStrip(*panel_data);
    timer     = &D_80148654;
    remaining = *timer - 1;
    *timer    = remaining;
    if (remaining == 0) {
        index = 0;
        panel_data += 0x607;
    loop_2:
        if (index < Party_CountOrder(PARTY_ORDER_FIELD)) {
            panel = (MenuPanelTask*)&g_UIPanelTasks[4].active + index;
            if (g_Characters[g_CharSlot[*(panel_data + (panel->unk_0B * 3) + panel->unk_0A)]].party_flags & 0x2) {
                panel->unk_0C = 1;
            }
            index += 1;
            goto loop_2; /* retail back edge: a while form needs a second register (82.19%) */
        }
        /* FAKE: the counter copy keeps retail's base register; the direct store scores 94.29%. */
        state_counter = &g_MenuStep.state;
        *state_counter += 1;
    }
}
