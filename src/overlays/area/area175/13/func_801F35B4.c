#include "area175_13.h"

MATCH void func_801F35B4(void) {
    func_801F36DC((s16) g_SpadWork->unk_2E, (s16) g_SpadWork->unk_30, g_SpadWork->unk_09);
    g_SpadWork->unk_09 += 1;
    if ((u8) g_SpadWork->unk_09 >= 0x1FU) {
        g_SpadWork->unk_09 = 0x1E;
        g_SpadWork->unk_01 += 1;
    }
}
