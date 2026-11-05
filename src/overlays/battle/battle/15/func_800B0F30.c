#include "battle_15.h"

MATCH void func_800B0F30(void) {
    func_800B0F9C();
    if ((s16)g_MenuCurrentPanel->x < 0x5B) {
        g_MenuCurrentPanel->x = g_MenuCurrentPanel->x + 32;
    }
    if ((s16)g_MenuCurrentPanel->x >= 0x5C) {
        g_MenuCurrentPanel->x = 91;
    }
}
