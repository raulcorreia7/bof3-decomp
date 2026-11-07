#include "game_00.h"

MATCH void func_801BD5A4(void) {
    Actor* work;
    Actor* tail;
    u8*    ids;

    work = g_Task;
    switch (work->header.step) {
        case 0:
            if (D_80145FBB[0].mode != 8) {
                work->header.mode = 1;
                ACTOR_CLEAR_STEP();
            }
            break;
        case 1:
            g_Task->param.unk_0B = Actor_FindFreeSlot();
            if (g_Task->param.unk_0B != GAME_NONE) {
                g_ActorSlots[g_Task->param.unk_0B].header.flags = 1;
                g_ActorSlots[g_Task->param.unk_0B].type         = 6;
                g_ActorSlots[g_Task->param.unk_0B].unk_06       = 1;
                tail                                            = g_Task;
                ids                                             = (u8*)g_GameState;
                g_ActorSlots[tail->param.unk_0B].scene_step     = 0;
                g_ActorSlots[tail->param.unk_0B].selection      = D_80181B28[ids[0x79]];
                g_ActorSlots[tail->param.unk_0B].unk_2E         = tail->unk_2E;
                g_ActorSlots[tail->param.unk_0B].unk_30         = tail->unk_30;
                tail->header.step                               = 2;
            } else {
                ACTOR_CLEAR_STEP();
            }
            break;
        case 2:
            if (g_ActorSlots[g_Task->param.unk_0B].header.flags == 0) {
                ACTOR_CLEAR_STEP();
            }
            break;
    }
    func_8014D978();
}
