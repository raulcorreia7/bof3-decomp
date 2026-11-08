#include "game_00.h"

MATCH void func_801BD5A4(void) {
    Actor* work;
    Actor* tail;
    u8*    ids;

    work = g_Task;
    switch (work->header.step) {
        case 0:
            if (g_Game.members[0].u.field.mode_12B.u8_value != 8) {
                work->header.mode = 1;
                ACTOR_CLEAR_STEP();
            }
            break;
        case 1:
            g_Task->param.unk_0B = Actor_FindFreeSlot();
            if (g_Task->param.unk_0B != GAME_NONE) {
                g_ActorSlots[g_Task->param.actor_slot].header.flags = 1;
                g_ActorSlots[g_Task->param.actor_slot].type         = 6;
                g_ActorSlots[g_Task->param.actor_slot].unk_06       = 1;
                tail                                                = g_Task;
                ids                                                 = (u8*)g_Game.current;
                g_ActorSlots[tail->param.actor_slot].scene_step     = 0;
                g_ActorSlots[tail->param.actor_slot].selection      = D_80181B28[ids[0x79]];
                g_ActorSlots[tail->param.actor_slot].unk_2E         = tail->screen_x;
                g_ActorSlots[tail->param.actor_slot].unk_30         = tail->screen_y;
                tail->header.step                                   = 2;
            } else {
                ACTOR_CLEAR_STEP();
            }
            break;
        case 2:
            if (g_ActorSlots[g_Task->param.actor_slot].header.flags == 0) {
                ACTOR_CLEAR_STEP();
            }
            break;
    }
    func_8014D978();
}
