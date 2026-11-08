/* Every step re-reads the scratchpad cell. */
#define TASK_VOLATILE
#include "area087_13.h"

MATCH void func_801F3120(void) {
    Actor* scratch;
    Actor* check;
    s32    key;
    /* FAKE: retail keeps the table offset in a1. */
    FAKE_REG(u32, i, "a1");
    u32 next;
    u32 mode;
    u8  state;
    u32 window;
    u32 window_span;

    scratch               = g_Task;
    scratch->option_flags = scratch->param.unk_0B;

    check = g_Task;
    if (check->param.unk_0B == 1) {
        key = g_GameContextSeed;
        i   = 0;
    scan:
        next = i;
        if (key == MEM(WorldMapKey, D_801F4DAC + next).key) {
            goto found; /* the found step also stores the key */
        }
        i = next + 4;
        goto scan; /* the key is always in the table */
    } else {
        scratch = g_Task;
        state   = scratch->param.unk_0B;
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
    window_span      = 0x10000;
    scratch          = g_Task;
    window           = 2;
    scratch->unk_18  = key;
    scratch->scale.x = 0;
    scratch->scale.y = window_span;
    scratch->unk_48  = window;
    scratch          = g_Task;
    scratch->timer   = 8;
    mode             = D_801F4DAE[i];
    goto tail;

check4:
    if (state == 4) {
        mode = 1;
    } else {
        return;
    }

arm:
    window_span      = 0x10000;
    scratch->scale.x = 0;
    scratch->scale.y = window_span;
    window           = 2;
    scratch->unk_48  = window;
    scratch          = g_Task;
    scratch->timer   = 8;
tail:
    Actor_SelectScript(mode);

    check              = g_Task;
    check->header.mode = window;
}
