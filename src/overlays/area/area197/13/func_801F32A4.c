#include "area197_13.h"

MATCH void func_801F32A4(Actor* actor) {
    TILE_1* tile;
    /* FAKE: retail reserves 16 more frame bytes than the two cell positions take; no statement uses them. */
    FAKE_STACK_PADS(u8, 16);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
    {
        Coord cell_x = {actor->vz};
        Coord cell_y = {actor->unk_18};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, -2, sizeof(DR_MODE));
    }

    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 1);
    Camera_ProjectPoint(&actor->vz, (DVECTOR*)&tile->x0);
    setRGB0(tile, 0, actor->unk_03, actor->unk_03);
    {
        Coord cell_x = {actor->vz};
        Coord cell_y = {actor->unk_18};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, -2, sizeof(TILE_1));
    }
}
