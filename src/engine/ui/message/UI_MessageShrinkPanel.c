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
    task           = (MenuPanelTask*)g_UIPanelCurrent;
    task->u.grow.w = (task->u.grow.w - task->u.grow.width_delta);
    task->pos.vx   = (task->pos.vx + (s16)task->u.grow.width_delta / 2);
    if ((task->u.grow.w << 16) < 0) {
        switch (task->mode) {
            case 0:
                if (task->flags & 0x2) {
                    task->pos.vx = ((g_UIPanelOrigins[1][g_UIPanelPlacement].x + (task->unk_0A >> 1)) << 4);
                } else {
                    task->pos.vx = ((g_UIPanelOrigins[0][g_UIPanelPlacement].x + (task->unk_0A >> 1)) << 4);
                }
                break;
            case 1:
                task->pos.vx = ((D_8017F930[g_UIMessageWindow.panel_index * 4] + (task->unk_0A >> 1)) << 4);
                break;
            default:
                g_UIPanelCurrent->pos.vx = ((D_8017F944[g_UIPanelPlacement][0] + (g_UIPanelCurrent->unk_0A >> 1)) << 4);
                break;
        }
        count++;
        g_UIPanelCurrent->u.grow.w = 0;
    }
    task           = (MenuPanelTask*)g_UIPanelCurrent;
    task->u.grow.h = (task->u.grow.h - task->u.grow.height_delta);
    task->pos.vy   = (task->pos.vy + (s16)task->u.grow.height_delta / 2);
    if ((task->u.grow.h << 16) < 0) {
        switch (task->mode) {
            case 0:
                if (task->flags & 0x2) {
                    task->pos.vy = ((g_UIPanelOrigins[1][g_UIPanelPlacement].y + (task->unk_0B >> 1)) << 4);
                } else {
                    task->pos.vy = ((g_UIPanelOrigins[0][g_UIPanelPlacement].y + (task->unk_0B >> 1)) << 4);
                }
                break;
            case 1:
                task->pos.vy = ((D_8017F930[1 + g_UIMessageWindow.panel_index * 4] + (task->unk_0B >> 1)) << 4);
                break;
            default:
                g_UIPanelCurrent->pos.vy = ((D_8017F944[g_UIPanelPlacement][1] + (g_UIPanelCurrent->unk_0B >> 1)) << 4);
                break;
        }
        count++;
        g_UIPanelCurrent->u.grow.h = 0;
    }
    if ((count & BYTE_MASK) == 2) {
        g_UIPanelCurrent->state++;
        return;
    }
    if (!(g_UIPanelCurrent->flags & 0x1)) {
        UI_WindowDrawBoxOutline(g_UIPanelCurrent->pos.vx >> 4, g_UIPanelCurrent->pos.vy >> 4, (g_UIPanelCurrent->u.grow.w >> 4), (g_UIPanelCurrent->u.grow.h >> 4));
    }
    if (g_UIPanelCurrent->mode == 0) {
        UI_MessageUpdateLayout();
    }
}
