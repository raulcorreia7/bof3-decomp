#include "battle_15.h"

MATCH void func_800B1664(void) {
    func_800B1728();
    if ((s16)g_MenuCurrentPanel->x >= 0xA4) {
        g_MenuCurrentPanel->x = g_MenuCurrentPanel->x - 32;
    }
    if ((s16)g_MenuCurrentPanel->x < 0xA3) {
        g_MenuCurrentPanel->x = 163;
    }
}
