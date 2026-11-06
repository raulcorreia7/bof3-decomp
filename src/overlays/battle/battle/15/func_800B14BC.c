#include "battle_15.h"

MATCH void func_800B14BC(void) {
    s16 current;

    func_800B1728();
    current               = g_MenuCurrentPanel->x;
    g_MenuCurrentPanel->x = (current >= 92 ? current - 32 : 91);
}
