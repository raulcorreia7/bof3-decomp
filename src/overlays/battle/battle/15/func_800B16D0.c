#include "battle_15.h"

MATCH void func_800B16D0(void) {
    s16 value;

    Battle_DrawCommandList();
    value = g_MenuCurrentPanel->pos.x;
    if (value >= 0x143) {
        func_80158E20();
    } else {
        g_MenuCurrentPanel->pos.x = (value + 32);
    }
}
