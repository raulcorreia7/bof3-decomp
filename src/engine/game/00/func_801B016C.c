#include "game_00.h"

MATCH void func_801B016C(void) {
    Actor* work;
    Actor* work2;
    Actor* pos;

    Actor_ClearVelocity();
    work          = SELF(Actor);
    work->timer   = 0;
    work2         = SELF(Actor);
    work->unk_18  = 0;
    work->unk_1C  = 0;
    work->gravity = 0;
    work2->unk_0A = 0;

    SELF(Actor)->unk_06       = 0;
    SELF(Actor)->option_flags = 0;
    SELF(Actor)->param.unk_0B = 0;

    pos                                      = SELF(Actor);
    COORD_INT(SELF(Actor)->pos.z)            = Area_HeightRead(pos->pos.x.fixed, pos->pos.y.fixed);
    g_Game.current->u.field.counter.value    = 3;
    g_Game.current->u.field.step.value       = 0;
    g_Game.current->u.field.mode.value       = 0;
    g_Game.current->status.field.flags.value = 0;
    SELF(Actor)->script_record               = 0xFF;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT) {
        SELF(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
        SELF(Actor)->header.mode = 0xC;
    } else if (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP) {
        SELF(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
        SELF(Actor)->header.mode = 0xD;
    } else {
        Actor_RequestRoute(SELF(Actor)->direction);
        SELF(Actor)->header.mode = SELF(Actor)->header.mode + 1;
    }
    ACTOR_CLEAR_STEP();
}
