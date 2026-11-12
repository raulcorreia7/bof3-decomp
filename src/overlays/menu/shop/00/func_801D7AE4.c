#include "shop_00.h"

MATCH void func_801D7AE4(void) {
    u8 count;

    func_801D8050(1);
    func_801D7E1C(D_80148656, D_80148654 * 0x20 + 0x98, 63, 0, 0xFF);
    count      = D_80148654 + 1;
    D_80148654 = count;
    if (count == 7) {
        D_80148654          = 0;
        g_MenuStep.step     = 1;
        g_MenuStep.sub_step = 0;
        g_MenuStep.state    = 0;
    }
}
