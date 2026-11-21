#include "game_00.h"

MATCH void func_801B87B8(void) {
    Actor* work;

    if (g_Task->timer == 0) {
        if (Area_TestCellCorners(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->voice_flags.scene_flag, 0xD0, 0) & BYTE_MASK) {
            func_801B8A0C();
            return;
        }
        func_801B8A9C();
        if (func_801B8D18() & BYTE_MASK) {
            Script_Request(g_Task->direction);
            g_Task->header.step = 3;
            g_Task->unk_03      = 0;
            return;
        }
        if ((func_801B9598() & BYTE_MASK) == 0) {
            work            = g_Task;
            work->direction = (work->direction + 1);
            func_801B9598();
        }
        switch (g_PadStates[0].held & INPUT_DIRECTIONAL) {
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
        Script_Request((g_Task->param.unk_0B + 8) & BYTE_MASK);
        Area_RunWalk();
    }
    g_Task->timer -= 1;
    Actor_UpdateMovement();
    Actor_StepAnimLoop();
}
