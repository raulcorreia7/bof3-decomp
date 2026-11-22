#include "game_00.h"

MATCH void func_801B016C(void) {
    Actor* work;
    Actor* work2;
    Actor* pos;

    Actor_ClearVelocity();
    work          = TASK(Actor);
    work->timer   = 0;
    work2         = TASK(Actor);
    work->unk_18  = 0;
    work->unk_1C  = 0;
    work->gravity = 0;
    work2->unk_0A = 0;

    TASK(Actor)->unk_06       = 0;
    TASK(Actor)->option_flags = 0;
    TASK(Actor)->param.unk_0B = 0;

    pos                                      = TASK(Actor);
    COORD_INT(TASK(Actor)->pos.z)            = Area_HeightRead(pos->pos.x.fixed, pos->pos.y.fixed);
    g_Game.current->u.field.counter.value    = 3;
    g_Game.current->u.field.step.value       = 0;
    g_Game.current->u.field.mode.value       = 0;
    g_Game.current->status.field.flags.value = 0;
    TASK(Actor)->script_record               = 0xFF;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
        TASK(Actor)->header.mode = 0xC;
    } else if (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
        TASK(Actor)->header.mode = 0xD;
    } else {
        Actor_RequestRoute(TASK(Actor)->direction);
        TASK(Actor)->header.mode = TASK(Actor)->header.mode + 1;
    }
    ACTOR_CLEAR_STEP();
}
