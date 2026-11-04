#include "area191_13.h"

MATCH void func_801F2D00(void) {
    u8 mode;

    mode = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = mode;
    if (mode & 0xFF) {
        g_SpadWork->tint.bytes.unk_5D += 1;
        g_SpadWork->tint.bytes.unk_5E += 1;
        g_SpadWork->tint.bytes.unk_5F += 1;
    } else {
        Message_StartAreaMessage(0x86);
        g_GameStateIndex = 2;
        g_SpadWork->unk_01 = 2;
    }
    func_801F2E34();
}
