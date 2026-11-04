#include "area175_13.h"

MATCH void func_801F3264(void) {
    g_SpadWork->unk_09 -= 1;
    if (g_SpadWork->unk_09 != 0) {
        g_SpadWork->tint.bytes.unk_5D += 6;
        g_SpadWork->tint.bytes.unk_5E += 6;
        g_SpadWork->tint.bytes.unk_5F += 6;
    } else {
        Message_StartAreaMessage(0x1F);
        g_GameStateIndex = 2;
        g_SpadWork->unk_01 = 2;
    }
    func_801F3438();
}
