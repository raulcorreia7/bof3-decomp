#include "engine/slus/slus.h"

/* advances the panel's two 12.4 axes by half their per-frame steps
 * and, when an axis reaches zero, snaps that axis to the mode-keyed table
 * value; completing both axes steps the panel state, otherwise the box is
 * redrawn through UI_WindowDrawBoxOutline.
 */
/* func_80159580 */
MATCH void UI_MessageShrinkPanel(void) {
    MenuPanelTask* task;
    s32            count;

    count          = 0;
    task           = (MenuPanelTask*)g_UiPanelCurrent;
    task->u.grow.w = (task->u.grow.w - task->u.grow.width_delta);
    task->pos.x    = (task->pos.x + (s16)task->u.grow.width_delta / 2);
    if ((task->u.grow.w << 16) < 0) {
        switch (task->mode) {
            case 0:
                if (task->flags & 0x2) {
                    task->pos.x = ((g_UiPanelOrigins[1][g_UiPanelPlacement].x + (task->unk_0A >> 1)) << 4);
                } else {
                    task->pos.x = ((g_UiPanelOrigins[0][g_UiPanelPlacement].x + (task->unk_0A >> 1)) << 4);
                }
                break;
            case 1:
                task->pos.x = ((D_8017F930[g_UiMessageWindow.panel_index * 4] + (task->unk_0A >> 1)) << 4);
                break;
            default:
                g_UiPanelCurrent->pos.x = ((D_8017F944[g_UiPanelPlacement][0] + (g_UiPanelCurrent->unk_0A >> 1)) << 4);
                break;
        }
        count++;
        g_UiPanelCurrent->u.grow.w = 0;
    }
    task           = (MenuPanelTask*)g_UiPanelCurrent;
    task->u.grow.h = (task->u.grow.h - task->u.grow.height_delta);
    task->pos.y    = (task->pos.y + (s16)task->u.grow.height_delta / 2);
    if ((task->u.grow.h << 16) < 0) {
        switch (task->mode) {
            case 0:
                if (task->flags & 0x2) {
                    task->pos.y = ((g_UiPanelOrigins[1][g_UiPanelPlacement].y + (task->unk_0B >> 1)) << 4);
                } else {
                    task->pos.y = ((g_UiPanelOrigins[0][g_UiPanelPlacement].y + (task->unk_0B >> 1)) << 4);
                }
                break;
            case 1:
                task->pos.y = ((D_8017F930[1 + g_UiMessageWindow.panel_index * 4] + (task->unk_0B >> 1)) << 4);
                break;
            default:
                g_UiPanelCurrent->pos.y = ((D_8017F944[g_UiPanelPlacement][1] + (g_UiPanelCurrent->unk_0B >> 1)) << 4);
                break;
        }
        count++;
        g_UiPanelCurrent->u.grow.h = 0;
    }
    if ((count & BYTE_MASK) == 2) {
        g_UiPanelCurrent->state++;
        return;
    }
    if (!(g_UiPanelCurrent->flags & 0x1)) {
        UI_WindowDrawBoxOutline((s16)g_UiPanelCurrent->pos.x >> 4, (s16)g_UiPanelCurrent->pos.y >> 4, (g_UiPanelCurrent->u.grow.w >> 4), (g_UiPanelCurrent->u.grow.h >> 4));
    }
    if (g_UiPanelCurrent->mode == 0) {
        UI_MessageUpdateLayout();
    }
}
