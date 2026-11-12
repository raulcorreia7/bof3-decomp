#include "battle_15.h"

MATCH void func_800B14BC(void) {
    s16 current;

    Battle_DrawCommandList();
    current                   = g_MenuCurrentPanel->pos.x;
    g_MenuCurrentPanel->pos.x = (current >= 92 ? current - 32 : 91);
}
