/* Every step re-reads the scratchpad cell. */
#define SPAD_WORK_VOLATILE
#include "area151_13.h"

MATCH void func_801F305C(void) {
    u8* scratch;
    u8* check;
    s32 key;
    /* FAKE: retail keeps the table offset in a1. */
    MATCH_REG(u32, i, "a1");
    u32 next;
    u32 mode;
    u32 window;
    u32 window_span;
    u8  state;

    scratch       = (u8*)g_SpadWork;
    scratch[0x07] = scratch[0x0B];

    check = (u8*)g_SpadWork;
    if (check[0x0B] == 1) {
        key = g_GameContextSeed;
        i   = 0;
    scan:
        next = i;
        if (key == MEM(WorldMapKey, D_801F4CE8 + next).key) {
            goto found;
        }
        i = next + 4;
        goto scan;
    } else {
        scratch = (u8*)g_SpadWork;
        state   = scratch[0x0B];
        if (state == 2) {
            mode = 3;
            goto arm;
        }
        if (state == 3) {
            mode = 0;
            goto arm;
        }
        goto check4;
    }

found:
    window_span             = 0x10000;
    scratch                 = (u8*)g_SpadWork;
    window                  = 2;
    *(u32*)(scratch + 0x18) = key;
    *(u32*)(scratch + 0x40) = 0;
    *(u32*)(scratch + 0x44) = window_span;
    scratch[0x48]           = window;
    scratch                 = (u8*)g_SpadWork;
    scratch[0x09]           = 8;
    mode                    = MEM(WorldMapKey, D_801F4CE8 + i).mode;
    goto tail;

check4:
    if (state == 4) {
        mode = 1;
    } else {
        return;
    }

arm:
    window_span             = 0x10000;
    *(u32*)(scratch + 0x40) = 0;
    *(u32*)(scratch + 0x44) = window_span;
    window                  = 2;
    scratch[0x48]           = window;
    scratch                 = (u8*)g_SpadWork;
    scratch[0x09]           = 8;
tail:
    Actor_SelectScript(mode);

    check       = (u8*)g_SpadWork;
    check[0x01] = window;
}
