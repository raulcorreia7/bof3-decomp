#include "area197_13.h"

MATCH void func_801F32A4(Actor* actor) {
    TILE_1* tile;
    /* FAKE: retail frame reserves 48 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 48);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 0x3C0, 0), 0);
    Area_AddCellPrim(actor->vz, actor->unk_18, -2, sizeof(DR_MODE));

    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 1);
    Area_ProjectPoint(&actor->vz, (DVECTOR*)&tile->x0);
    tile->r0 = 0;
    tile->g0 = actor->unk_03;
    tile->b0 = actor->unk_03;
    Area_AddCellPrim(actor->vz, actor->unk_18, -2, sizeof(TILE_1));
}
