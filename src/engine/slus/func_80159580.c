#include "engine/slus/slus.h"

/* advances the panel's two 12.4 axes by half their per-frame steps
 * and, when an axis reaches zero, snaps that axis to the mode-keyed table
 * value; completing both axes steps the panel state, otherwise the box is
 * redrawn through func_80159FA0.
 */
MATCH void func_80159580(void) {
    MenuPanelTask* task;
    s32            count;

    count        = 0;
    task         = (MenuPanelTask*)g_MenuCurrentPanel;
    task->unk_10 = (task->unk_10 - task->unk_14);
    task->x      = (task->x + (s16)task->unk_14 / 2);
    if ((task->unk_10 << 0x10) < 0) {
        switch (task->unk_02) {
            case 0:
                if (task->flags & 2) {
                    task->x = ((g_MenuPanelOrigins[16 + D_801490CE * 2] + (task->unk_0A >> 1)) << 4);
                } else {
                    task->x = ((g_MenuPanelOrigins[D_801490CE * 2] + (task->unk_0A >> 1)) << 4);
                }
                break;
            case 1:
                task->x = ((D_8017F930[D_801490BC.panel_index * 4] + (task->unk_0A >> 1)) << 4);
                break;
            default:
                g_MenuCurrentPanel->x = ((D_8017F944[D_801490CE][0] + (g_MenuCurrentPanel->unk_0A >> 1)) << 4);
                break;
        }
        count++;
        g_MenuCurrentPanel->unk_10 = 0;
    }
    task         = (MenuPanelTask*)g_MenuCurrentPanel;
    task->unk_12 = (task->unk_12 - task->unk_16);
    task->y      = (task->y + (s16)task->unk_16 / 2);
    if ((task->unk_12 << 0x10) < 0) {
        switch (task->unk_02) {
            case 0:
                if (task->flags & 2) {
                    task->y = ((g_MenuPanelOrigins[17 + D_801490CE * 2] + (task->unk_0B >> 1)) << 4);
                } else {
                    task->y = ((g_MenuPanelOrigins[1 + D_801490CE * 2] + (task->unk_0B >> 1)) << 4);
                }
                break;
            case 1:
                task->y = ((D_8017F930[1 + D_801490BC.panel_index * 4] + (task->unk_0B >> 1)) << 4);
                break;
            default:
                g_MenuCurrentPanel->y = ((D_8017F944[D_801490CE][1] + (g_MenuCurrentPanel->unk_0B >> 1)) << 4);
                break;
        }
        count++;
        g_MenuCurrentPanel->unk_12 = 0;
    }
    if ((count & 0xFF) == 2) {
        g_MenuCurrentPanel->state++;
        return;
    }
    if (!(g_MenuCurrentPanel->flags & 1)) {
        func_80159FA0((s16)g_MenuCurrentPanel->x >> 4, (s16)g_MenuCurrentPanel->y >> 4,
                      (g_MenuCurrentPanel->unk_10 >> 4), (g_MenuCurrentPanel->unk_12 >> 4));
    }
    if (g_MenuCurrentPanel->unk_02 == 0) {
        UI_UpdateLayout();
    }
}
