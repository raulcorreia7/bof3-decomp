#include "game_00.h"

MATCH void func_801B87B8(void) {
    Actor* work;

    if (g_Task->timer == 0) {
        if (func_801C472C(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0xD0, 0) & BYTE_MASK) {
            func_801B8A0C();
            return;
        }
        func_801B8A9C();
        if (func_801B8D18() & BYTE_MASK) {
            Actor_RequestScript(g_Task->direction_08);
            g_Task->header.step = 3;
            g_Task->unk_03      = 0;
            return;
        }
        if ((func_801B9598() & BYTE_MASK) == 0) {
            work               = g_Task;
            work->direction_08 = (work->direction_08 + 1);
            func_801B9598();
        }
        switch (g_InputHeld & INPUT_DIRECTIONAL) {
            case PADLup:
                g_Task->param.unk_0B = 0;
                break;
            case PADLup | PADLright:
                g_Task->param.unk_0B = 1;
                break;
            case PADLright:
                g_Task->param.unk_0B = 2;
                break;
            case PADLright | PADLdown:
                g_Task->param.unk_0B = 3;
                break;
            case PADLdown:
                g_Task->param.unk_0B = 4;
                break;
            case PADLdown | PADLleft:
                g_Task->param.unk_0B = 5;
                break;
            case PADLleft:
                g_Task->param.unk_0B = 6;
                break;
            case PADLleft | PADLup:
                g_Task->param.unk_0B = 7;
                break;
        }
        Actor_RequestScript((g_Task->param.unk_0B + 8) & BYTE_MASK);
        func_801C24D0();
    }
    g_Task->timer -= 1;
    Actor_UpdateMovement();
    Actor_StepAnimLoop();
}
