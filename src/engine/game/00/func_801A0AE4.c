#include "game_00.h"

MATCH void func_801A0AE4(Actor* record) {
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

    spad_a = TASK(Actor);
    saved  = spad_a->direction;
    D_801C83BC[spad_a->header.step](record, 0, 1);
    spad_b = TASK(Actor);
    if (spad_b->timer == 0) {
        mode  = record->unk_78;
        param = g_RouteSpeedScale[mode];
        if (record->unk_7B == 0) {
            if ((mode != 0) && (D_801C83BC[spad_b->header.step](record, param, 2) & BYTE_MASK)) {
                Actor_TurnRandom(record);
                if (TASK(Actor)->timer != 0) {
                    timer = RANDOM_MASK(3) + 3;
                    goto block_7;
                }
            }
        } else {
            D_801C83BC[spad_b->header.step](record, param, 2);
            timer = record->unk_7B - 1;
        block_7:
            record->unk_7B = timer;
        }
        result = func_801A2A04(record);
        if (((result & BYTE_MASK) != GAME_NONE) && (TASK(Actor)->timer != 0)) {
            spad_c                   = TASK(Actor);
            spad_c->unk_03           = spad_c->header.mode;
            TASK(Actor)->header.mode = 0xAU;
            record->unk_79           = result;
            TASK(Actor)->direction   = (saved & 0x7);
            spad_d                   = TASK(Actor);
            spad_d->unk_0A           = 0;
            spad_d->timer            = 0U;
            func_801A3B7C(record);
            spad_e = TASK(Actor);
            if (spad_e->header.mode != 0xA) {
                spad_e->direction = saved;
                /* Shared tail: resume the route and run the step. */
                goto block_14;
            }
        } else {
            TASK(Actor)->timer     = 0U;
            TASK(Actor)->direction = saved;
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
