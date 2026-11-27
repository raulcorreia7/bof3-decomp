#include "engine/slus/slus.h"

/* advances the panel's two scroll axes toward the pending values,
 * taking the axis target from the mode-keyed D_8017F9xx tables on expiry and
 * committing the panel position to the window driver.
 */
/* func_8015920C */
MATCH void UI_MessageGrowPanel(void) {
    MenuPanelTask* panel;
    u16            next_x;
    u16            next_y;
    u8             advanced;

    panel = g_UIPanelCurrent;

    panel->u.grow.w = panel->u.grow.w + panel->u.grow.width_delta;
    panel->pos.vx -= (s16)panel->u.grow.width_delta / 2;

    advanced = 0;
    if (panel->unk_0A < ((s16)panel->u.grow.w >> 4)) {
        switch (panel->mode) {
            case 0:
                if (panel->flags & 0x2) {
                    next_x = g_UIPanelOrigins[1][g_UIPanelPlacement].x * 0x10;
                } else {
                    next_x = g_UIPanelOrigins[0][g_UIPanelPlacement].x * 0x10;
                }
                panel->pos.vx = next_x;
                break;
            case 1:
                panel->pos.vx = panel->u.grow.target_x * 16;
                break;
            default:
                g_UIPanelCurrent->pos.vx = D_8017F944[g_UIPanelPlacement][0] * 16;
                break;
        }
        advanced++;
        g_UIPanelCurrent->u.grow.w = (g_UIPanelCurrent->unk_0A * 0x10);
    }

    panel = g_UIPanelCurrent;

    panel->u.grow.h = panel->u.grow.h + panel->u.grow.height_delta;
    panel->pos.vy -= (s16)panel->u.grow.height_delta / 2;

    if (panel->unk_0B < ((s16)panel->u.grow.h >> 4)) {
        switch (panel->mode) {
            case 0:
                if (panel->flags & 0x2) {
                    next_y = g_UIPanelOrigins[1][g_UIPanelPlacement].y * 0x10;
                } else {
                    next_y = g_UIPanelOrigins[0][g_UIPanelPlacement].y * 0x10;
                }
                panel->pos.vy = next_y;
                break;
            case 1:
                panel->pos.vy = panel->u.grow.target_y * 16;
                break;
            default:
                g_UIPanelCurrent->pos.vy = D_8017F944[g_UIPanelPlacement][1] * 16;
                break;
        }
        advanced++;
        g_UIPanelCurrent->u.grow.h = (g_UIPanelCurrent->unk_0B * 0x10);
    }

    if ((g_UIPanelCurrent->flags & 0x1) == 0) {
        u32 width  = (g_UIPanelCurrent->u.grow.w >> 4) & BYTE_MASK;
        u32 height = (g_UIPanelCurrent->u.grow.h >> 4) & BYTE_MASK;

        UI_WindowDrawBoxOutline(g_UIPanelCurrent->pos.vx >> 4, g_UIPanelCurrent->pos.vy >> 4, width, height);
    }

    if ((advanced & BYTE_MASK) == 2) {
        g_UIPanelCurrent->state += 1;
    }
}
