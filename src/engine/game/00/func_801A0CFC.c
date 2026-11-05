#include "game_00.h"

MATCH void func_801A0CFC(Actor* entity) {
    s32 value;
    u8* work;
    u8  saved;
    u8  mode;
    u8  param;

    saved = g_Task->direction_08;
    D_801C83BC[g_Task->step](entity, 0, 1);
    if (g_Task->unk_09 != 0) {
        func_801A253C(entity);
        return;
    }
    mode  = entity->unk_78;
    param = g_RouteSpeedScale[mode];
    if (entity->unk_7B == 0) {
        if (mode == 0) {
            return;
        }
        if (D_801C83BC[g_Task->step](entity, param, 2) != 0) {
            value = ((s32 (*)(Actor*))func_801A2C94)(entity);
            if (g_Task->unk_09 != 0) {
                entity->unk_7B = ((RANDOM_MASK(3)) + 3);
            }
        } else {
            value = 0xFF;
        }
    } else {
        D_801C83BC[g_Task->step](entity, param, 2);
        value = ((s32 (*)(Actor*, s32))func_801A2ED4)(entity, 1);
        entity->unk_7B -= 1;
    }
    if (((value & BYTE_MASK) != GAME_NONE) && (g_Task->unk_09 != 0)) {
        g_Task->unk_03       = g_Task->mode;
        g_Task->mode         = 0x0A;
        entity->unk_79       = (value & 7);
        g_Task->direction_08 = (saved & 7);
        work                 = (u8*)g_Task;
        work[0x0A]           = 0;
        work[9]              = 0;
        func_801A3B7C(entity);
        if (g_Task->mode == 0x0A) {
            return;
        }
        g_Task->direction_08 = saved;
    } else {
        g_Task->unk_09       = 0;
        g_Task->direction_08 = saved;
    }
    func_801A2AE4(entity, saved);
    func_801A253C(entity);
}
