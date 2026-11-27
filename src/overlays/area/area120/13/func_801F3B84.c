#include "area120_13.h"

MATCH void func_801F3B84(void) {
    s32 arg;

    if (g_GameEntryState == GAME_MODE_BATTLE && g_GameEntrySubstate != g_GameEntryState) {
        SELF(Actor)->header.step -= 1;
    }
    if ((MEM(u32, SELF(Actor)->vx) & 0xFFFF00) == 0x20800) {
        SELF(Actor)->header.step = 4;
    }
    if ((MEM(u32, SELF(Actor)->vx) & 0xFFFF00) == 0x10600) {
        SELF(Actor)->header.step = 6;
    }
    if ((MEM(u32, SELF(Actor)->vx) & 0xFFFF00) == 0x20600) {
        SELF(Actor)->header.step = 6;
    }
    if ((MEM(u32, SELF(Actor)->vx) & 0xFFFF00) == 0x30600) {
        SELF(Actor)->header.step = 5;
    }
    if ((MEM(u32, SELF(Actor)->vx) & 0xFFFF00) == 0x40600) {
        SELF(Actor)->header.step = 3;
    }
    arg = 0x80;
    if ((MEM(u32, SELF(Actor)->vx) & 0xFFFF00) == 0x10300) {
        arg = (g_Battle.unk_24[4] * 6 + 0x3F) & 0xF8;
    }
    func_801F3F5C(arg, 0x40, 1, 0);
}
