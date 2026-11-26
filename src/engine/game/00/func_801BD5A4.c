#include "game_00.h"

MATCH void func_801BD5A4(void) {
    Actor* work;
    Actor* tail;
    u8*    ids;

    work = SELF(Actor);
    switch (work->header.step) {
        case 0:
            if (g_Game.members[0].u.field.mode.unsigned_value != 8) {
                work->header.mode = 1;
                ACTOR_CLEAR_STEP();
            }
            break;
        case 1:
            SELF(Actor)->param.unk_0B = Actor_FindFreeSpawned();
            if (SELF(Actor)->param.unk_0B != GAME_NONE) {
                g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 6;
                g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06       = 1;
                tail                                                        = SELF(Actor);
                ids                                                         = (u8*)g_Game.current;
                g_SpawnedActors[tail->param.actor_slot].vx                  = 0;
                g_SpawnedActors[tail->param.actor_slot].selection           = D_80181B28[ids[0x79]];
                g_SpawnedActors[tail->param.actor_slot].screen_x            = tail->screen_x;
                g_SpawnedActors[tail->param.actor_slot].screen_y            = tail->screen_y;
                tail->header.step                                           = 2;
            } else {
                ACTOR_CLEAR_STEP();
            }
            break;
        case 2:
            if (g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags == 0) {
                ACTOR_CLEAR_STEP();
            }
            break;
    }
    Script_AnimStepLoop();
}
