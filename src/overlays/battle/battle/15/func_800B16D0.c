#include "battle_15.h"

MATCH void func_800B16D0(void) {
    s16 value;

    func_800B1728();
    value = (s16)g_MenuCurrentPanel->x;
    if (value >= 0x143) {
        func_80158E20();
    } else {
        g_MenuCurrentPanel->x = (u16)(value + 32);
    }
}
