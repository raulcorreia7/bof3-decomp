#include "batl_ovr_00.h"

MATCH void func_801EEEB8(void) {
    func_801EF318();
    func_801EF180(0x80);

    if (WINDOW_EFFECT_IDLE()) {
        D_801463B0 = 0x2C;
        g_BattleUIStep += 1;
    }
}
