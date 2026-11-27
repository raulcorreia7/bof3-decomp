#include "engine/game/00/game_00.h"

/* func_8019DAA0 */
/* Draws one dust puff as a semi-transparent screen quad. */
MATCH s32 Actor_ShatterDrawPuff(s32* puff, s16 quad_size, u8 brightness) {
    DVECTOR   screen;
    u16       size[2];
    POLY_FT4* primitive;

    primitive = (POLY_FT4*)g_GfxPrimCursor;

    SetPolyFT4(primitive);
    PSX_SET_SEMI_TRANSPARENT(primitive);

    Camera_ProjectPoint(puff, &screen);
    size[0] = quad_size;
    size[1] = quad_size;
    Game_ProjectWorldPoint(puff, size, size);

    setXY4(primitive, (u16)screen.vx - ((s16)size[0] >> 1), (u16)screen.vy - ((s16)size[1] >> 1), ((u16)screen.vx - ((s16)size[0] >> 1)) + size[0], (u16)screen.vy - ((s16)size[1] >> 1),
           (u16)screen.vx - ((s16)size[0] >> 1), ((u16)screen.vy - ((s16)size[1] >> 1)) + size[1], ((u16)screen.vx - ((s16)size[0] >> 1)) + size[0], ((u16)screen.vy - ((s16)size[1] >> 1)) + size[1]);
    setUV4(primitive, 224u, 48u, 255u, 48u, 224u, 79u, 255u, 79u);
    setClut(primitive, 160, STAGE_PALETTE_Y + 3);
    primitive->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
    setRGB0(primitive, brightness, brightness, brightness);

    {
        Coord cell_x = {puff[0]};
        Coord cell_y = {puff[1]};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, 2, sizeof(POLY_FT4));
    }
}
