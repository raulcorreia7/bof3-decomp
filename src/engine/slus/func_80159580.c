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
    task->pos.x  = (task->pos.x + (s16)task->unk_14 / 2);
    if ((task->unk_10 << 0x10) < 0) {
        switch (task->unk_02) {
            case 0:
                if (task->flags & 2) {
                    task->pos.x = ((g_MenuPanelOrigins[16 + D_801490CE * 2] + (task->unk_0A >> 1)) << 4);
                } else {
                    task->pos.x = ((g_MenuPanelOrigins[D_801490CE * 2] + (task->unk_0A >> 1)) << 4);
                }
                break;
            case 1:
                task->pos.x = ((D_8017F930[g_MessageWindow.panel_index * 4] + (task->unk_0A >> 1)) << 4);
                break;
            default:
                g_MenuCurrentPanel->pos.x = ((D_8017F944[D_801490CE][0] + (g_MenuCurrentPanel->unk_0A >> 1)) << 4);
                break;
        }
        count++;
        g_MenuCurrentPanel->unk_10 = 0;
    }
    task         = (MenuPanelTask*)g_MenuCurrentPanel;
    task->unk_12 = (task->unk_12 - task->unk_16);
    task->pos.y  = (task->pos.y + (s16)task->unk_16 / 2);
    if ((task->unk_12 << 0x10) < 0) {
        switch (task->unk_02) {
            case 0:
                if (task->flags & 2) {
                    task->pos.y = ((g_MenuPanelOrigins[17 + D_801490CE * 2] + (task->unk_0B >> 1)) << 4);
                } else {
                    task->pos.y = ((g_MenuPanelOrigins[1 + D_801490CE * 2] + (task->unk_0B >> 1)) << 4);
                }
                break;
            case 1:
                task->pos.y = ((D_8017F930[1 + g_MessageWindow.panel_index * 4] + (task->unk_0B >> 1)) << 4);
                break;
            default:
                g_MenuCurrentPanel->pos.y = ((D_8017F944[D_801490CE][1] + (g_MenuCurrentPanel->unk_0B >> 1)) << 4);
                break;
        }
        count++;
        g_MenuCurrentPanel->unk_12 = 0;
    }
    if ((count & BYTE_MASK) == 2) {
        g_MenuCurrentPanel->state++;
        return;
    }
    if (!(g_MenuCurrentPanel->flags & 1)) {
        func_80159FA0((s16)g_MenuCurrentPanel->pos.x >> 4, (s16)g_MenuCurrentPanel->pos.y >> 4,
                      (g_MenuCurrentPanel->unk_10 >> 4), (g_MenuCurrentPanel->unk_12 >> 4));
    }
    if (g_MenuCurrentPanel->unk_02 == 0) {
        UI_UpdateLayout();
    }
}
