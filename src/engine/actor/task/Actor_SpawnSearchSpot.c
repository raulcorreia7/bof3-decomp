#include "engine/game/00/game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

/* func_801A7330 */
/* Spawns a searchable object from a type 9 setup record; its flag bit says whether it was already searched. */
MATCH void Actor_SpawnSearchSpot(const volatile u8* data) {
    s16    dist;
    s16    slot;
    u8     mode;
    Actor* work;
    Actor* w2;
    Actor* rec;

    slot = g_ScratchPad.cells.halves[0];
    if (slot >= ENTITY_MAX) {
        return;
    }

    SELF_SET(&g_Actors[slot]);
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    g_ScratchPad.cells.ray.y = (u16)((data[1] << 8) | data[2]);

    Actor_ResetMotion();
    Area_SceneSelectRecord(g_ScratchPad.cells.ray.y);

    SELF(Actor)->header.flags = ACTOR_FLAG_IN_USE;

    work                                               = SELF(Actor);
    g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_x = (work->pos.x.fixed = (data[5] << 16) | ((data[4] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read before the shadow store. */
    FAKE_BARRIER();

    g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_y = (work->pos.y.fixed = (data[7] << 16) | ((data[6] != 0) ? 0x8000 : 0));

    g_Actors[g_ScratchPad.cells.halves[0]].unk_88 = 0;

    dist = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);

    w2                   = SELF(Actor);
    w2->header.mode      = ACTOR_MODE_REQUEST_SCRIPT;
    COORD_INT(w2->pos.z) = (u16)dist;
    ACTOR_CLEAR_STEP();
    /* FAKE: barrier pins the flags store before the route-index load. */
    FAKE_BARRIER();

    SELF(Actor)->direction = data[0] & 0xF;
    SELF(Actor)->unk_06    = data[0] >> 4;

    g_Actors[g_ScratchPad.cells.halves[0]].unk_78 = 0;
    g_Actors[g_ScratchPad.cells.halves[0]].unk_94 = 0x7F;

    Actor_SetOptionFlags((u8*)(data + 0xB));

    if (data[3] & 0x80) {
        SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    SELF(Actor)->tint.bytes.rgb.r = 0;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->tint.bytes.rgb.g = 0;
    SELF(Actor)->tint.bytes.flags = data[3] & 0xF;
    SELF(Actor)->draw_layer       = 6;

    rec                                           = SELF(Actor);
    g_Actors[g_ScratchPad.cells.halves[0]].unk_7C = 0;
    /* FAKE: the block keeps the packed store ahead of the record stores. */
    do {
        rec->unk_18 = (data[9] << 8) | ((const u8*)data)[0xA];
    } while (0);
    SELF(Actor)->unk_05       = data[8];
    SELF(Actor)->param.unk_0B = data[0xC];
    SELF(Actor)->mirror       = (SELF(Actor)->option_flags >> ACTOR_OPT_NO_SCRIPT_START) & 0x1;

    mode = SELF(Actor)->unk_05;
    if ((D_80144FC4[mode >> 3] >> (mode & 0x7)) & 0x1) {
        if (data[0xC] & 0x1) {
            SELF(Actor)->header.flags = 0;
            return;
        }
        /* The 16-bit halves of the two position words have no named members. */
        if (COORD_FRAC(SELF(Actor)->pos.x) == 0 && COORD_FRAC(SELF(Actor)->pos.y) == 0) {
            Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0x10);
        }
        Script_Select(1);
    } else {
        Script_Select(0);
    }

    g_ScratchPad.cells.halves[0]++;
}
