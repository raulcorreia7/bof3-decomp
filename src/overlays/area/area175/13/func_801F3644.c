#include "area175_13.h"

MATCH void func_801F3644(void) {
    u8 mode;

    func_801F36DC((s16)g_SpadWork->unk_2E, (s16)g_SpadWork->unk_30, g_SpadWork->unk_09);
    mode = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_SpadWork->unk_01 += 1;
    }
}
