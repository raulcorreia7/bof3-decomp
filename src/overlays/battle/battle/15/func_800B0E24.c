#include "battle_15.h"

MATCH void func_800B0E24(void) {
    s16 current;

    func_800B0F9C();
    current                   = g_MenuCurrentPanel->pos.x;
    g_MenuCurrentPanel->pos.x = (current < 91 ? current + 32 : 91);
}
