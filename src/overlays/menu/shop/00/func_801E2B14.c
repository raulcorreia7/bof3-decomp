#include "shop_00.h"

MATCH void func_801E2B14(void) {
    MenuPanelTask* task_root;
    u16            next_val;
    s16            clamped;

    task_root         = g_UiPanelCurrent;
    next_val          = task_root->pos.vy - MENU_PANEL_STEP_Y;
    task_root->pos.vy = next_val;
    if ((s16)next_val >= -0x13) {
        clamped           = MENU_PANEL_HIDDEN_Y;
        task_root->pos.vy = clamped;
        task_root->state  = 0;
    }
}
