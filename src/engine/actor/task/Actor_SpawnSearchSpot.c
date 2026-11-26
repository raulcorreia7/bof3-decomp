#include "engine/game/00/game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

/* func_801A7330 */
/* Spawns a searchable object from a type 9 setup record; its flag bit says whether it was already searched. */
MATCH void Actor_SpawnSearchSpot(const volatile u8* data) {
    s16*   counter = (s16*)&g_ScratchPad;
    s16    dist;
    s16    slot;
    u8     mode;
    Actor* work;
    Actor* w2;
    Actor* rec;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    g_ScratchPad.cells.ray.y = (u16)((data[1] << 8) | data[2]);

    Actor_ResetMotion();
    Area_SceneSelectRecord(g_ScratchPad.cells.ray.y);

    TASK(Actor)->header.flags = ACTOR_FLAG_IN_USE;

    work                           = TASK(Actor);
    g_Actors[*counter].walk_dest_x = (work->pos.x.fixed = (data[5] << 16) | ((data[4] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read before the shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].walk_dest_y = (work->pos.y.fixed = (data[7] << 16) | ((data[6] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read against merging. */
    FAKE_BARRIER();

    g_Actors[*counter].unk_88 = 0;

    dist = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);

    w2                   = TASK(Actor);
    w2->header.mode      = ACTOR_MODE_REQUEST_SCRIPT;
    COORD_INT(w2->pos.z) = (u16)dist;
    ACTOR_CLEAR_STEP();
    /* FAKE: barrier pins the flags store before the route-index load. */
    FAKE_BARRIER();

    TASK(Actor)->direction = data[0] & 0xF;
    TASK(Actor)->unk_06    = data[0] >> 4;

    g_Actors[*counter].unk_78 = 0;
    g_Actors[*counter].unk_94 = 0x7F;

    Actor_SetOptionFlags((u8*)(data + 0xB));

    if (data[3] & 0x80) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    TASK(Actor)->tint.bytes.rgb.r = 0;
    TASK(Actor)->tint.bytes.rgb.b = 0;
    TASK(Actor)->tint.bytes.rgb.g = 0;
    TASK(Actor)->tint.bytes.flags = data[3] & 0xF;
    TASK(Actor)->draw_layer       = 6;

    rec                       = TASK(Actor);
    g_Actors[*counter].unk_7C = 0;
    /* FAKE: lock keeps the packed store ahead of the record stores. */
    FAKE_ORDER_LOCK(rec->unk_18 = (data[9] << 8) | ((const u8*)data)[0xA]);
    TASK(Actor)->unk_05       = data[8];
    TASK(Actor)->param.unk_0B = data[0xC];
    TASK(Actor)->mirror       = (TASK(Actor)->option_flags >> ACTOR_OPT_NO_SCRIPT_START) & 0x1;

    mode = TASK(Actor)->unk_05;
    if ((D_80144FC4[mode >> 3] >> (mode & 0x7)) & 0x1) {
        if (data[0xC] & 0x1) {
            TASK(Actor)->header.flags = 0;
            return;
        }
        /* The 16-bit halves of the two position words have no named members. */
        if (COORD_FRAC(TASK(Actor)->pos.x) == 0 && COORD_FRAC(TASK(Actor)->pos.y) == 0) {
            Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), 0x10);
        }
        Script_Select(1);
    } else {
        Script_Select(0);
    }

    (FAKE_VOLATILE(u16, g_ScratchPad)) = (FAKE_VOLATILE(u16, g_ScratchPad)) + 1;
}
