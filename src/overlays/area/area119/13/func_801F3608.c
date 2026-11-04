#include "area119_13.h"

MATCH void func_801F3608(void) {
    u8  frame = g_SpadWork->unk_09;
    s32 level = 0x80;

    if (frame < 0x20) {
        level = frame * 4;
    }
    if (frame >= 0x59) {
        level = 0x80 - (frame - 0x58) * 4;
    }
    if (frame >= 0x78) {
        Actor_Clear();
    }
    func_801F369C(level);
    g_SpadWork->unk_09++;
}
