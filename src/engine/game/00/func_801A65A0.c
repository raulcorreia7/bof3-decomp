#include "game_00.h"

MATCH void func_801A65A0(u8* script) {
    s16*   counter = (s16*)&D_1F800000;
    s16    slot;
    s32    coord_x;
    s32    coord_y;
    s16    dist;
    Actor* work;
    Actor* record;
    s32    slot_off;

    slot = *counter;
    if (slot < ENTITY_MAX) {
        TASK_SET(&g_Actors[slot]);
        g_CurrentActor = &g_Actors[slot];
        func_801A4AA8();
        Party_LoadMemberSprite(script[1], script[0xF]);
        g_Task->header.flags = ACTOR_FLAG_IN_USE;
        coord_x              = script[5] << 16;
        slot_off             = *counter * ACTOR_SIZE;
        work                 = g_Task;
        if (script[4] != 0) {
            coord_x |= 0x8000;
        }
        work->pos.x.fixed             = coord_x;
        g_ActorWalkDestX[*counter][0] = coord_x;
        /* FAKE: barrier pins the x store before the y loads. */
        FAKE_BARRIER();
        g_ActorWalkDestY[*counter][0] = work->pos.y.fixed = (script[7] << 16) | (script[6] != 0 ? 0x8000 : 0);
        /* FAKE: forces the counter re-read before the next shadow store. */
        FAKE_BARRIER();
        D_80146910[*counter][0]  = 0;
        dist                     = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
        record                   = g_Task;
        COORD_INT(record->pos.z) = (u16)dist;
        record->header.mode      = script[8];

        g_Task->header.step                            = script[0xA];
        g_Task->direction_08                           = script[0] & 0xF;
        g_Task->unk_06                                 = script[0] >> 4;
        FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[2];
        FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[3];
        FIELD(u16, D_80146904, *counter * ACTOR_SIZE)  = (u16)(script[0xD] | (script[0xC] << 8));
        FIELD(u8, &D_801468FF, *counter * ACTOR_SIZE)  = script[0xE];
        FIELD(u8, D_80146900, *counter * ACTOR_SIZE)   = script[9];
        FIELD(u8, D_8014691C, *counter * ACTOR_SIZE)   = 0x7F;
        Actor_SetOptionFlags((u8*)script + 0xB);
        g_Task->tint.bytes.unk_5D = 0;
        g_Task->tint.bytes.unk_5F = 0;
        g_Task->tint.bytes.unk_5E = 0;
        g_Task->tint.bytes.flags  = 2;
        func_801A4914();
        *counter = (u16)(*counter + 1);
    }
}
