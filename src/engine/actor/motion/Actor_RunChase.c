#include "engine/game/00/game_00.h"

/* func_801A0F24 */
/* Mode 2: walks toward the leader once the leader is inside the actor's box. */
MATCH void Actor_RunChase(Actor* record) {
    u8     result;
    u8     mode;
    u8     param;
    u8     saved;
    Actor* spad_e;
    Actor* spad_d;
    Actor* spad_c;
    Actor* spad_a;
    Actor* spad_b;

    spad_a = TASK(Actor);
    saved  = spad_a->direction;
    g_ActorPaceSteps[spad_a->header.step](record, 0, 1);
    spad_b = TASK(Actor);
    if (spad_b->timer == 0) {
        mode  = record->unk_78;
        param = g_RouteSpeedScale[mode];
        if (record->unk_7B == 0) {
            if (mode != 0) {
                if (g_ActorPaceSteps[spad_b->header.step](record, param, 2) & BYTE_MASK) {
                    result = Actor_PickChaseFacing(record);
                    if (TASK(Actor)->timer != 0) {
                        record->unk_7B = RANDOM_MASK(3) + 3;
                    }
                } else {
                    result = 0xFF;
                }
                /* Both result paths converge on the work-field update. */
                goto block_8;
            }
        } else {
            g_ActorPaceSteps[spad_b->header.step](record, param, 2);
            result = Actor_PickFacingByLeaderDistance(record, 0U);
            record->unk_7B -= 1;
        block_8:
            if (((result & BYTE_MASK) != GAME_NONE) && (spad_c = TASK(Actor), (spad_c->timer != 0))) {
                spad_c->unk_03           = spad_c->header.mode;
                TASK(Actor)->header.mode = ACTOR_MODE_TURN;
                record->unk_79           = result & 0x7;
                TASK(Actor)->direction   = (saved & 0x7);
                spad_d                   = TASK(Actor);
                spad_d->unk_0A           = 0;
                spad_d->timer            = 0U;
                Actor_RunTurn(record);
                spad_e = TASK(Actor);
                if (spad_e->header.mode != ACTOR_MODE_TURN) {
                    spad_e->direction = saved;
                    /* Shared tail: restore the route and run the step. */
                    goto block_13;
                }
            } else {
                TASK(Actor)->timer     = 0U;
                TASK(Actor)->direction = saved;
            block_13:
                func_801A2AE4(record, saved);
                /* Both paths finish through the idle handler. */
                goto block_14;
            }
        }
    } else {
    block_14:
        Area_SetXFixed(record);
    }
}
