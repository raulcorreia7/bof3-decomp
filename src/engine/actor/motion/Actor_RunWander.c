#include "engine/game/00/game_00.h"

/* func_801A0AE4 */
/* Mode 0: walks in short legs, turning at random, and turns away from a blocked facing. */
MATCH void Actor_RunWander(Actor* record) {
    u8     result;
    u8     mode;
    u8     param;
    u8     saved;
    u8     timer;
    Actor* spad_a;
    Actor* spad_b;
    Actor* spad_c;
    Actor* spad_d;
    Actor* spad_e;

    spad_a = SELF(Actor);
    saved  = spad_a->direction;
    g_ActorPaceSteps[spad_a->header.step](record, 0, 1);
    spad_b = SELF(Actor);
    if (spad_b->timer == 0) {
        mode  = record->unk_78;
        param = g_RouteSpeedScale[mode];
        if (record->unk_7B == 0) {
            if ((mode != 0) && (g_ActorPaceSteps[spad_b->header.step](record, param, 2) & BYTE_MASK)) {
                Actor_TurnRandom(record);
                if (SELF(Actor)->timer != 0) {
                    timer = RANDOM_MASK(3) + 3;
                    goto block_7;
                }
            }
        } else {
            g_ActorPaceSteps[spad_b->header.step](record, param, 2);
            timer = record->unk_7B - 1;
        block_7:
            record->unk_7B = timer;
        }
        result = Actor_FindFreeFacing(record);
        if (((result & BYTE_MASK) != GAME_NONE) && (SELF(Actor)->timer != 0)) {
            spad_c                   = SELF(Actor);
            spad_c->unk_03           = spad_c->header.mode;
            SELF(Actor)->header.mode = ACTOR_MODE_TURN;
            record->unk_79           = result;
            SELF(Actor)->direction   = (saved & 0x7);
            spad_d                   = SELF(Actor);
            spad_d->unk_0A           = 0;
            spad_d->timer            = 0U;
            Actor_RunTurn(record);
            spad_e = SELF(Actor);
            if (spad_e->header.mode != ACTOR_MODE_TURN) {
                spad_e->direction = saved;
                /* Shared tail: resume the route and run the step. */
                goto block_14;
            }
        } else {
            SELF(Actor)->timer     = 0U;
            SELF(Actor)->direction = saved;
        block_14:
            func_801A2AE4(record, saved);
            /* Shared tail: run the route step and finish. */
            goto block_15;
        }
    } else {
    block_15:
        Area_SetXFixed(record);
    }
}
