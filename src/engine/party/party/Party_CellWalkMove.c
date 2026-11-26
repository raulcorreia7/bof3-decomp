#include "engine/game/00/game_00.h"

/* func_801B87B8 */
/* Walks the actor by the pad direction until its footprint is clear of the cell, or hands over to the jump. */
MATCH void Party_CellWalkMove(void) {
    Actor* work;

    if (TASK(Actor)->timer == 0) {
        if (Area_CellTestCorners(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0xD0, 0) & BYTE_MASK) {
            Party_CellWalkEnd();
            return;
        }
        func_801B8A9C();
        if (func_801B8D18() & BYTE_MASK) {
            Script_Request(TASK(Actor)->direction);
            TASK(Actor)->header.step = PARTY_MOVE_STEP_JUMP;
            TASK(Actor)->unk_03      = 0;
            return;
        }
        if ((func_801B9598() & BYTE_MASK) == 0) {
            work            = TASK(Actor);
            work->direction = (work->direction + 1);
            func_801B9598();
        }
        switch (g_PadStates[0].held & INPUT_DIRECTIONAL) {
            case PADLup:
                TASK(Actor)->param.unk_0B = 0;
                break;
            case PADLup | PADLright:
                TASK(Actor)->param.unk_0B = 1;
                break;
            case PADLright:
                TASK(Actor)->param.unk_0B = 2;
                break;
            case PADLright | PADLdown:
                TASK(Actor)->param.unk_0B = 3;
                break;
            case PADLdown:
                TASK(Actor)->param.unk_0B = 4;
                break;
            case PADLdown | PADLleft:
                TASK(Actor)->param.unk_0B = 5;
                break;
            case PADLleft:
                TASK(Actor)->param.unk_0B = 6;
                break;
            case PADLleft | PADLup:
                TASK(Actor)->param.unk_0B = 7;
                break;
        }
        Script_Request((TASK(Actor)->param.unk_0B + 8) & BYTE_MASK);
        Area_RunWalk();
    }
    TASK(Actor)->timer -= 1;
    Actor_MovementUpdate();
    Script_AnimStepLoop();
}
