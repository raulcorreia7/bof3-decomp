#include "shop_00.h"

MATCH void func_801E2D1C(void) {
    MenuPanelTask* task_root;
    u16            next_val;

    task_root    = g_MenuCurrentPanel;
    next_val     = task_root->y - 0x10;
    task_root->y = next_val;
    if ((s16)next_val < 0x3E) {
        task_root->y     = 62;
        task_root->state = 0;
    }
}
