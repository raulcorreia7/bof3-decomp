#include "shop_00.h"

MATCH void func_801E2B14(void) {
    MenuPanelTask* task_root;
    u16            next_val;
    s16            clamped;

    task_root        = g_MenuCurrentPanel;
    next_val         = task_root->pos.y - 0x10;
    task_root->pos.y = next_val;
    if ((s16)next_val >= -0x13) {
        clamped          = -0x14;
        task_root->pos.y = clamped;
        task_root->state = 0;
    }
}
