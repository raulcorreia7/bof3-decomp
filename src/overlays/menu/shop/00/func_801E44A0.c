#include "shop_00.h"

MATCH void func_801E44A0(void) {
    MenuPanelTask* task_root;
    u16            next_val;

    task_root    = g_MenuCurrentPanel;
    next_val     = task_root->y - 0x10;
    task_root->y = next_val;
    if ((s16)next_val < 0x80) {
        task_root->y     = 128;
        task_root->state = 0;
    }
}
