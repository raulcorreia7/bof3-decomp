#include "battle_15.h"

MATCH void func_800B0E6C(void) {
    s16 value;

    func_800B0F9C();
    value = g_MenuCurrentPanel->pos.x;
    if (value < -0xA4) {
        func_80158E20();
    } else {
        g_MenuCurrentPanel->pos.x = (value - 32);
    }
}
