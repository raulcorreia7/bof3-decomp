#include "engine/game/00/game_00.h"

/* func_801A65A0 */
/* Spawns a party member actor from a scene script record. */
MATCH void Actor_SpawnPartyFromRecord(u8* script) {
    s16*   counter = (s16*)&g_ScratchPad;
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
        Actor_ResetMotion();
        Party_MemberLoadSprite(script[1], script[0xF]);
        TASK(Actor)->header.flags = ACTOR_FLAG_IN_USE;
        coord_x                   = script[5] << 16;
        slot_off                  = *counter * ACTOR_SIZE;
        work                      = TASK(Actor);
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
        dist                     = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
        record                   = TASK(Actor);
        COORD_INT(record->pos.z) = (u16)dist;
        record->header.mode      = script[8];

        TASK(Actor)->header.step                       = script[0xA];
        TASK(Actor)->direction                         = script[0] & 0xF;
        TASK(Actor)->unk_06                            = script[0] >> 4;
        FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[2];
        FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[3];
        FIELD(u16, D_80146904, *counter * ACTOR_SIZE)  = (u16)(script[0xD] | (script[0xC] << 8));
        FIELD(u8, &D_801468FF, *counter * ACTOR_SIZE)  = script[0xE];
        FIELD(u8, D_80146900, *counter * ACTOR_SIZE)   = script[9];
        FIELD(u8, D_8014691C, *counter * ACTOR_SIZE)   = 0x7F;
        Actor_SetOptionFlags((u8*)script + 0xB);
        TASK(Actor)->tint.bytes.rgb.r = 0;
        TASK(Actor)->tint.bytes.rgb.b = 0;
        TASK(Actor)->tint.bytes.rgb.g = 0;
        TASK(Actor)->tint.bytes.flags = 2;
        Actor_StartFacingScript();
        *counter = (u16)(*counter + 1);
    }
}
