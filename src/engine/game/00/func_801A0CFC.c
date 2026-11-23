#include "game_00.h"

MATCH void func_801A0CFC(Actor* entity) {
    s32    value;
    Actor* work;
    u8     saved;
    u8     mode;
    u8     param;

    saved = TASK(Actor)->direction;
    D_801C83BC[TASK(Actor)->header.step](entity, 0, 1);
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
        if (D_801C83BC[TASK(Actor)->header.step](entity, param, 2) != 0) {
            value = ((s32 (*)(Actor*))func_801A2C94)(entity);
            if (TASK(Actor)->timer != 0) {
                entity->unk_7B = (RANDOM_MASK(3) + 3);
            }
        } else {
            value = 0xFF;
        }
    } else {
        D_801C83BC[TASK(Actor)->header.step](entity, param, 2);
        value = ((s32 (*)(Actor*, s32))func_801A2ED4)(entity, 1);
        entity->unk_7B -= 1;
    }
    if (((value & BYTE_MASK) != GAME_NONE) && (TASK(Actor)->timer != 0)) {
        TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
        TASK(Actor)->header.mode = 0x0A;
        entity->unk_79           = (value & 0x7);
        TASK(Actor)->direction   = (saved & 0x7);
        work                     = TASK(Actor);
        work->unk_0A             = 0;
        work->timer              = 0;
        func_801A3B7C(entity);
        if (TASK(Actor)->header.mode == 0x0A) {
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
