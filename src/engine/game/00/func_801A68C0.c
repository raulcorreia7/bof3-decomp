#include "game_00.h"

MATCH void func_801A68C0(u8* script) {
    s16*   counter = (s16*)&D_1F800000;
    s16    slot;
    s32    tile;
    Actor* rows;
    Actor* work;
    s32    x;
    s32    y;
    u32    offset;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    tile               = g_GameAreaId;
    offset             = script[9] * 8;
    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];
    rows               = g_Actors;

    tile                 = FIELD(s32, g_AreaLoads[tile], 0x8u) + offset;
    g_Task->direction_08 = script[0] & 0xF;
    func_801A4AA8();
    SYS_InitScratchpad((u8*)tile);
    func_801A4B80(4);

    work = g_Task;
    x    = script[2] << 16;
    if (script[1] != 0) {
        x |= 32768;
    }
    work->pos.x.fixed = x;
    y                 = script[4] << 16;
    if (script[3] != 0) {
        y |= 32768;
    }
    work->pos.y.fixed = y;

    COORD_INT(g_Task->pos.z) = Area_SampleHeight(work->pos.x.fixed, y);
    g_Task->header.mode      = script[5];
    g_Task->header.step      = script[7];
    g_Task->unk_06           = script[0] >> 4;
    g_Task->gravity          = 0;
    g_Task->unk_1C           = 0;
    g_Task->unk_18           = 0;
    g_Task->state_70.word    = FIELD(u8, g_Task->range_54.table, 0x2u);

    rows[*counter].unk_88                               = 0;
    rows[*counter].walk_dest_y                          = 0;
    FIELD(s32, g_ActorWalkDestX, *counter * ACTOR_SIZE) = 0;
    FIELD(u8, &D_801468FF, *counter * ACTOR_SIZE)       = script[0xA];
    FIELD(u8, D_80146900, *counter * ACTOR_SIZE)        = script[6];
    FIELD(u16, D_80146904, *counter * ACTOR_SIZE)       = script[0xD] | (script[0xC] << 8);
    FIELD(u8, D_8014691C, *counter * ACTOR_SIZE)        = 0x7F;

    Actor_SetOptionFlags(script + 8);

    g_Task->tint.signed_bytes.unk_5D = -0x80;
    g_Task->tint.signed_bytes.unk_5F = -0x80;
    g_Task->tint.signed_bytes.unk_5E = -0x80;
    g_Task->tint.bytes.flags         = 2;

    if (D_80146900[*counter][0] == 0) {
        Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), 0x10);
        if (COORD_FRAC(g_Task->pos.x) != 0) {
            Area_SetCellCode((s16)((u16)COORD_INT(g_Task->pos.x) + 1), COORD_INT(g_Task->pos.y), 0x10);
        }
        if (COORD_FRAC(g_Task->pos.y) != 0) {
            Area_SetCellCode(COORD_INT(g_Task->pos.x), (s16)((u16)COORD_INT(g_Task->pos.y) + 1), 0x10);
        }
        if ((COORD_FRAC(g_Task->pos.x) != 0) && (COORD_FRAC(g_Task->pos.y) != 0)) {
            Area_SetCellCode((s16)((u16)COORD_INT(g_Task->pos.x) + 1), (s16)((u16)COORD_INT(g_Task->pos.y) + 1), 0x10);
        }
    }

    (VOL(u16, D_1F800000)) = (VOL(u16, D_1F800000)) + 1;
}
