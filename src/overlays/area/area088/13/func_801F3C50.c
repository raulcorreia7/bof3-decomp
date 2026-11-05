/* Every step re-reads the scratchpad cell. */
#define SPAD_WORK_VOLATILE
#include "area088_13.h"

MATCH void func_801F3C50(void) {
    Actor* scratch;
    Actor* check;
    s32    key;
    /* FAKE: retail keeps the table offset in a1. */
    MATCH_REG(u32, i, "a1");
    u32 next;
    u32 mode;
    u8  state;
    u32 window;
    u32 window_span;

    scratch               = g_SpadWork;
    scratch->option_flags = scratch->unk_0B;

    check = g_SpadWork;
    if (check->unk_0B == 1) {
        key = g_GameContextSeed;
        i   = 0;
    scan:
        next = i;
        if (key == MEM(WorldMapKey, D_801F5900 + next).key) {
            goto found; /* the found step also stores the key */
        }
        i = next + 4;
        goto scan; /* the key is always in the table */
    } else {
        scratch = g_SpadWork;
        state   = scratch->unk_0B;
        if (state == 2) {
            mode = 3;
            goto arm; /* steps 2 and 3 share the re-arm block */
        }
        if (state == 3) {
            mode = 0;
            goto arm; /* steps 2 and 3 share the re-arm block */
        }
        goto check4;
    }

found:
    window_span     = 0x10000;
    scratch         = g_SpadWork;
    window          = 2;
    scratch->unk_18 = key;
    scratch->unk_40 = 0;
    scratch->unk_44 = window_span;
    scratch->unk_48 = window;
    scratch         = g_SpadWork;
    scratch->unk_09 = 8;
    mode            = D_801F5902[i];
    goto tail;

check4:
    if (state == 4) {
        mode = 1;
    } else {
        return;
    }

arm:
    window_span     = 0x10000;
    scratch->unk_40 = 0;
    scratch->unk_44 = window_span;
    window          = 2;
    scratch->unk_48 = window;
    scratch         = g_SpadWork;
    scratch->unk_09 = 8;
tail:
    Actor_SelectScript(mode);

    check         = g_SpadWork;
    check->unk_01 = window;
}
