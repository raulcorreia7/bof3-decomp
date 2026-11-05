#include "battle_15.h"

MATCH void func_800B0E24(void) {
    s16 current;

    func_800B0F9C();
    current               = (s16)g_MenuCurrentPanel->x;
    g_MenuCurrentPanel->x = (u16)(current < 91 ? current + 32 : 91);
}
