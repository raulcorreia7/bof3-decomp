#include "battle_15.h"

MATCH void func_800B0EC4(void) {
    func_800B0F9C();
    if ((s16)g_MenuCurrentPanel->pos.x >= 0x12) {
        g_MenuCurrentPanel->pos.x = g_MenuCurrentPanel->pos.x - 32;
    }
    if ((s16)g_MenuCurrentPanel->pos.x < 0x11) {
        g_MenuCurrentPanel->pos.x = 17;
    }
}
