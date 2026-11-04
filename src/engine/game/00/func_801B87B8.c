#include "game_00.h"

MATCH void func_801B87B8(void) {
    Actor* work;

    if (g_SpadWork->unk_09 == 0) {
        if (func_801C472C(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0xD0, 0) & BYTE_MASK) {
            func_801B8A0C();
            return;
        }
        func_801B8A9C();
        if (func_801B8D18() & BYTE_MASK) {
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->state_02 = 3;
            g_SpadWork->unk_03   = 0;
            return;
        }
        if ((func_801B9598() & BYTE_MASK) == 0) {
            work               = g_SpadWork;
            work->direction_08 = (u8)(work->direction_08 + 1);
            func_801B9598();
        }
        switch (g_InputHeld & INPUT_DIRECTIONAL) {
            case 0x1000:
                g_SpadWork->unk_0B = 0;
                break;
            case 0x3000:
                g_SpadWork->unk_0B = 1;
                break;
            case 0x2000:
                g_SpadWork->unk_0B = 2;
                break;
            case 0x6000:
                g_SpadWork->unk_0B = 3;
                break;
            case 0x4000:
                g_SpadWork->unk_0B = 4;
                break;
            case 0xC000:
                g_SpadWork->unk_0B = 5;
                break;
            case 0x8000:
                g_SpadWork->unk_0B = 6;
                break;
            case 0x9000:
                g_SpadWork->unk_0B = 7;
                break;
        }
        Actor_RequestScript((g_SpadWork->unk_0B + 8) & BYTE_MASK);
        func_801C24D0();
    }
    g_SpadWork->unk_09 -= 1;
    func_801B0DFC();
    func_8014D978();
}
