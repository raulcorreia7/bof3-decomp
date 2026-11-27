#include "engine/game/00/game_00.h"

/* func_801B87B8 */
/* Walks the actor by the pad direction until its footprint is clear of the cell, or hands over to the jump. */
MATCH void Party_CellWalkMove(void) {
    Actor* work;

    if (SELF(Actor)->timer == 0) {
        if (Area_CellTestCorners(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->voice_flags.scene_flag, 0xD0, 0) & BYTE_MASK) {
            Party_CellWalkEnd();
            return;
        }
        func_801B8A9C();
        if (func_801B8D18() & BYTE_MASK) {
            Script_Request(SELF(Actor)->direction);
            SELF(Actor)->header.step = PARTY_MOVE_STEP_JUMP;
            SELF(Actor)->unk_03      = 0;
            return;
        }
        if ((func_801B9598() & BYTE_MASK) == 0) {
            work            = SELF(Actor);
            work->direction = (work->direction + 1);
            func_801B9598();
        }
        switch (g_PadStates[0].held & INPUT_DIRECTIONAL) {
            case PADLup:
                SELF(Actor)->param.unk_0B = 0;
                break;
            case PADLup | PADLright:
                SELF(Actor)->param.unk_0B = 1;
                break;
            case PADLright:
                SELF(Actor)->param.unk_0B = 2;
                break;
            case PADLright | PADLdown:
                SELF(Actor)->param.unk_0B = 3;
                break;
            case PADLdown:
                SELF(Actor)->param.unk_0B = 4;
                break;
            case PADLdown | PADLleft:
                SELF(Actor)->param.unk_0B = 5;
                break;
            case PADLleft:
                SELF(Actor)->param.unk_0B = 6;
                break;
            case PADLleft | PADLup:
                SELF(Actor)->param.unk_0B = 7;
                break;
        }
        Script_Request((SELF(Actor)->param.unk_0B + 8) & BYTE_MASK);
        Area_RunWalk();
    }
    SELF(Actor)->timer -= 1;
    Actor_MovementUpdate();
    Script_AnimStepLoop();
}
