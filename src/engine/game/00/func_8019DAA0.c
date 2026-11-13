#include "game_00.h"

MATCH s32 func_8019DAA0(s32* spawn_record, s16 spawn_offset, u8 spawn_count) {
    DVECTOR screen;
    u16     size[2];
    /* FAKE: retail reserves frame bytes above size[] that no statement uses. */
    FAKE_STACK_PADS(u8, 12);
    POLY_FT4* primitive;

    primitive = (POLY_FT4*)g_GfxPrimCursor;

    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);

    Area_ProjectPoint(spawn_record, &screen);
    size[0] = spawn_offset;
    size[1] = spawn_offset;
    Game_ProjectWorldPoint(spawn_record, size, size);

    setXY4(primitive, (u16)screen.vx - ((s16)size[0] >> 1), (u16)screen.vy - ((s16)size[1] >> 1), ((u16)screen.vx - ((s16)size[0] >> 1)) + size[0], (u16)screen.vy - ((s16)size[1] >> 1),
           (u16)screen.vx - ((s16)size[0] >> 1), ((u16)screen.vy - ((s16)size[1] >> 1)) + size[1], ((u16)screen.vx - ((s16)size[0] >> 1)) + size[0], ((u16)screen.vy - ((s16)size[1] >> 1)) + size[1]);
    setUV4(primitive, 224u, 48u, 255u, 48u, 224u, 79u, 255u, 79u);
    setClut(primitive, 160, STAGE_PALETTE_Y + 3);
    primitive->tpage = GetTPage(0, 1, 704, 256);
    setRGB0(primitive, spawn_count, spawn_count, spawn_count);

    Area_AddCellPrim(spawn_record[0], spawn_record[1], 2, sizeof(POLY_FT4));
}
