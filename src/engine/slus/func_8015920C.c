#include "engine/slus/slus.h"

/* advances the panel's two scroll axes toward the pending values,
 * taking the axis target from the mode-keyed D_8017F9xx tables on expiry and
 * committing the panel position to the window driver.
 */
MATCH void func_8015920C(void) {
    MenuPanelTask* panel;
    u16            next_x;
    u16            next_y;
    u8             advanced;

    panel = g_MenuCurrentPanel;

    panel->unk_10 = panel->unk_10 + panel->unk_14;
    panel->x -= (s16)panel->unk_14 / 2;

    advanced = 0;
    if (panel->unk_0A < ((s16)panel->unk_10 >> 4)) {
        switch (panel->unk_02) {
            case 0:
                if (panel->flags & 2) {
                    next_x = g_MenuPanelOrigins[16 + D_801490CE * 2] * 0x10;
                } else {
                    next_x = g_MenuPanelOrigins[D_801490CE * 2] * 0x10;
                }
                panel->x = next_x;
                break;
            case 1:
                panel->x = panel->unk_18 * 16;
                break;
            default:
                g_MenuCurrentPanel->x = D_8017F944[D_801490CE][0] * 16;
                break;
        }
        advanced++;
        g_MenuCurrentPanel->unk_10 = (g_MenuCurrentPanel->unk_0A * 0x10);
    }

    panel = g_MenuCurrentPanel;

    panel->unk_12 = panel->unk_12 + panel->unk_16;
    panel->y -= (s16)panel->unk_16 / 2;

    if (panel->unk_0B < ((s16)panel->unk_12 >> 4)) {
        switch (panel->unk_02) {
            case 0:
                if (panel->flags & 2) {
                    next_y = g_MenuPanelOrigins[17 + D_801490CE * 2] * 0x10;
                } else {
                    next_y = g_MenuPanelOrigins[1 + D_801490CE * 2] * 0x10;
                }
                panel->y = next_y;
                break;
            case 1:
                panel->y = panel->unk_1A * 16;
                break;
            default:
                g_MenuCurrentPanel->y = D_8017F944[D_801490CE][1] * 16;
                break;
        }
        advanced++;
        g_MenuCurrentPanel->unk_12 = (g_MenuCurrentPanel->unk_0B * 0x10);
    }

    if ((g_MenuCurrentPanel->flags & 1) == 0) {
        u32 width  = (g_MenuCurrentPanel->unk_10 >> 4) & BYTE_MASK;
        u32 height = (g_MenuCurrentPanel->unk_12 >> 4) & BYTE_MASK;

        func_80159FA0((s16)g_MenuCurrentPanel->x >> 4, (s16)g_MenuCurrentPanel->y >> 4, width, height);
    }

    if ((advanced & BYTE_MASK) == 2) {
        g_MenuCurrentPanel->state += 1;
    }
}
