#include "area100_13.h"

MATCH void func_801F34FC(void) {
    s32 base;
    u8  state;

    base  = (SYS_TestFlag(g_SceneEventFlags, 147) != 0) << 1;
    state = SYS_TestFlag(g_SceneEventFlags, 148) ? (base | 0x1) : base;
    switch (state) {
        case 0:
        default:
            func_8019FA28(0x3B, 0x478000, 0x2A0000, 0x81);
            break;
        case 1:
            func_8019FA28(0x24, 0x478000, 0x240000, 0x81);
            break;
        case 2:
            func_8019FA28(0x74, 0x478000, 0x340000, 0x81);
            break;
        case 3:
            func_8019FA28(0x70, 0xC8000, 0x580000, 0x81);
            break;
    }
}
