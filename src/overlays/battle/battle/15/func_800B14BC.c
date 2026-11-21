#include "battle_15.h"

MATCH void func_800B14BC(void) {
    s16 current;

    Battle_DrawCommandList();
    current                 = g_UiPanelCurrent->pos.x;
    g_UiPanelCurrent->pos.x = (current >= 92 ? current - 32 : 91);
}
