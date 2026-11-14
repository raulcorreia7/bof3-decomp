#include "game_00.h"

MATCH void func_801A0F24(Actor* record) {
    u8     result;
    u8     mode;
    u8     param;
    u8     saved;
    Actor* spad_e;
    Actor* spad_d;
    Actor* spad_c;
    Actor* spad_a;
    Actor* spad_b;

    spad_a = g_Task;
    saved  = spad_a->direction_08;
    D_801C83BC[spad_a->header.step](record, 0, 1);
    spad_b = g_Task;
    if (spad_b->timer == 0) {
        mode  = record->unk_78;
        param = g_RouteSpeedScale[mode];
        if (record->unk_7B == 0) {
            if (mode != 0) {
                if (D_801C83BC[spad_b->header.step](record, param, 2) & BYTE_MASK) {
                    result = func_801A2DB4(record);
                    if (g_Task->timer != 0) {
                        record->unk_7B = RANDOM_MASK(3) + 3;
                    }
                } else {
                    result = 0xFF;
                }
                /* Both result paths converge on the work-field update. */
                goto block_8;
            }
        } else {
            D_801C83BC[spad_b->header.step](record, param, 2);
            result = func_801A2ED4(record, 0U);
            record->unk_7B -= 1;
        block_8:
            if (((result & BYTE_MASK) != GAME_NONE) && (spad_c = g_Task, (spad_c->timer != 0))) {
                spad_c->unk_03       = spad_c->header.mode;
                g_Task->header.mode  = 0xAU;
                record->unk_79       = result & 0x7;
                g_Task->direction_08 = (saved & 0x7);
                spad_d               = g_Task;
                spad_d->unk_0A       = 0;
                spad_d->timer        = 0U;
                func_801A3B7C(record);
                spad_e = g_Task;
                if (spad_e->header.mode != 0xA) {
                    spad_e->direction_08 = saved;
                    /* Shared tail: restore the route and run the step. */
                    goto block_13;
                }
            } else {
                g_Task->timer        = 0U;
                g_Task->direction_08 = saved;
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
