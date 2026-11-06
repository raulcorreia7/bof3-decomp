#include "battle_15.h"

MATCH void func_800B0A54(void) {
    s16 value;

    value                 = g_MenuCurrentPanel->y;
    g_MenuCurrentPanel->y = (value < 0x29 ? value + 16 : 41);
    func_800B0B0C(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y);
}
