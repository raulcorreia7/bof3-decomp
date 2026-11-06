#include "shop_00.h"

MATCH void func_801E4278(void) {
    MenuPanelTask* task_root;
    u16            next_val;
    s16            clamp_val;

    task_root        = g_MenuCurrentPanel;
    next_val         = (task_root->pos.x - 0x20);
    task_root->pos.x = next_val;
    if ((s16)next_val < -120) {
        clamp_val        = -120;
        task_root->pos.x = clamp_val;
        task_root->state = 0;
    }
}
