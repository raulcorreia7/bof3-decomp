#include "battle_15.h"

MATCH void func_800B14BC(void) {
    s16 current;

    Battle_DrawCommandList();
    current                  = g_UIPanelCurrent->pos.vx;
    g_UIPanelCurrent->pos.vx = (current >= 92 ? current - 32 : 91);
}
