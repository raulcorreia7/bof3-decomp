#include "battle_15.h"

MATCH void func_800B1664(void) {
    Battle_DrawCommandList();
    if ((s16)g_MenuCurrentPanel->pos.x >= 164) {
        g_MenuCurrentPanel->pos.x = g_MenuCurrentPanel->pos.x - 32;
    }
    if ((s16)g_MenuCurrentPanel->pos.x < 163) {
        g_MenuCurrentPanel->pos.x = 163;
    }
}
