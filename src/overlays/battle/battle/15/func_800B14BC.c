#include "battle_15.h"

MATCH void func_800B14BC(void) {
    s16 current;

    Battle_DrawCommandList();
    current                  = g_UiPanelCurrent->pos.vx;
    g_UiPanelCurrent->pos.vx = (current >= 92 ? current - 32 : 91);
}
