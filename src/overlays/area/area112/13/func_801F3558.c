#include "area112_13.h"

MATCH void func_801F3558(void) {
    s32 base;
    u8  state;

    base  = (SYS_TestFlag(g_SceneEventFlags, 52) != 0) << 1;
    state = SYS_TestFlag(g_SceneEventFlags, 53) ? (base | 0x1) : base;
    switch (state) {
        case 0:
        default:
            func_8019FA28(0x91, 0xA8000, 0x630000, 0x84);
            break;
        case 1:
            func_8019FA28(0x8F, 0x388000, 0x650000, 0x81);
            break;
        case 2:
            func_8019FA28(0x92, 0x458000, 0x2B0000, 0x81);
            break;
        case 3:
            func_8019FA28(0x64, 0x468000, 0x340000, 0x81);
            break;
    }
}
