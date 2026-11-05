#include "area104_14.h"

MATCH void func_801F5254(void) {
    Actor* w;
    s8     clamped;
    s8     stored;
    u32    step;
    u8     timer;
    u8     held;
    u8     level;

    timer = g_SpadWork->unk_0A;
    if (timer != 0) {
        g_SpadWork->unk_0A = timer - 1;
    }
    if (g_SpadWork->unk_0A == 0) {
        if (g_InputHeld & D_80145AB6) {
            held = g_SpadWork->unk_0B;
            if (held < 0x40U) {
                g_SpadWork->unk_0B = held + 1;
            }
            if (g_SpadWork->unk_0B == 0x40) {
                g_SpadWork->unk_0A = 0x1E;
            }
        } else {
            level = g_SpadWork->unk_0B;
            if (level != 0) {
                if (level >= 0x31U) {
                    step = 3;
                } else {
                    step = 1;
                    if (level >= 0x21U) {
                        step = 2;
                    }
                }
                if (g_SpadWork->state_02 != 0) {
                    g_SpadWork->unk_0B -= step >> 1;
                    if (g_FrameCount & 1) {
                        g_SpadWork->unk_0B -= step & 1;
                    }
                } else {
                    g_SpadWork->unk_0B -= step;
                }
            }
        }
        w       = g_SpadWork;
        clamped = (s8)w->unk_0B;
        if (clamped >= 0) {
            stored = 0x40;
            if (clamped < 0x41) {
                stored = clamped;
            }
        } else {
            stored = 0;
        }
        w->unk_0B = (u8)stored;
    }
}
