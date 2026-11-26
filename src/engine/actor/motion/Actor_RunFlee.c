#include "engine/game/00/game_00.h"

/* func_801A0CFC */
/* Mode 1: walks away from the leader once the leader is inside the actor's box. */
MATCH void Actor_RunFlee(Actor* entity) {
    s32    value;
    Actor* work;
    u8     saved;
    u8     mode;
    u8     param;

    saved = TASK(Actor)->direction;
    g_ActorPaceSteps[TASK(Actor)->header.step](entity, 0, 1);
    if (TASK(Actor)->timer != 0) {
        Area_SetXFixed(entity);
        return;
    }
    mode  = entity->unk_78;
    param = g_RouteSpeedScale[mode];
    if (entity->unk_7B == 0) {
        if (mode == 0) {
            return;
        }
        if (g_ActorPaceSteps[TASK(Actor)->header.step](entity, param, 2) != 0) {
            value = ((s32 (*)(Actor*))Actor_PickFleeFacing)(entity);
            if (TASK(Actor)->timer != 0) {
                entity->unk_7B = (RANDOM_MASK(3) + 3);
            }
        } else {
            value = 0xFF;
        }
    } else {
        g_ActorPaceSteps[TASK(Actor)->header.step](entity, param, 2);
        value = ((s32 (*)(Actor*, s32))Actor_PickFacingByLeaderDistance)(entity, 1);
        entity->unk_7B -= 1;
    }
    if (((value & BYTE_MASK) != GAME_NONE) && (TASK(Actor)->timer != 0)) {
        TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
        TASK(Actor)->header.mode = ACTOR_MODE_TURN;
        entity->unk_79           = (value & 0x7);
        TASK(Actor)->direction   = (saved & 0x7);
        work                     = TASK(Actor);
        work->unk_0A             = 0;
        work->timer              = 0;
        Actor_RunTurn(entity);
        if (TASK(Actor)->header.mode == ACTOR_MODE_TURN) {
            return;
        }
        TASK(Actor)->direction = saved;
    } else {
        TASK(Actor)->timer     = 0;
        TASK(Actor)->direction = saved;
    }
    func_801A2AE4(entity, saved);
    Area_SetXFixed(entity);
}
