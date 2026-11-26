#include "area132_13.h"

/* Draws the spawn slot's glow as a textured quad; its corner shades come from the slot's colour and shade flags. */
/* func_801F3560 */
#ifdef NON_MATCHING
NON_MATCHING void func_801F3560(AreaSpawnSlot* slot) {
    DVECTOR   screen;
    u16       size[2];
    s32*      object;
    POLY_FT4* primitive;
    u8        flags;
    u8        red;
    u8        green;
    u8        blue;

    /* FAKE: retail reserves 32 frame bytes that no local or callee buffer explains. */
    FAKE_STACK_PADS(u8, 0x20);

    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));
    Area_CellAddPrim(slot->pos.x.fixed, slot->pos.y.fixed, 3, sizeof(DR_MODE));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);

    object = &slot->pos.x.fixed;
    Camera_ProjectPoint(object, &screen);
    size[0] = slot->radius;
    size[1] = slot->radius;
    Game_ProjectWorldPoint(object, size, size);

    setXYWH(primitive, screen.vx - ((s16)size[0] >> 1), screen.vy - ((s16)size[1] >> 1), size[0], size[1]);
    setUV4(primitive, 224, 48, 255, 48, 224, 79, 255, 79);
    primitive->clut  = GetClut(160, STAGE_PALETTE_Y + 3);
    primitive->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 704, 256);
    flags            = slot->core_shade;
    red              = 0;
    if ((flags & 4) != 0) {
        red = slot->unk_03;
    }
    green = 0;
    if ((flags & 2) != 0) {
        green = slot->unk_03;
    }
    blue = 0;
    if ((flags & 1) != 0) {
        blue = slot->unk_03;
    }
    setRGB0(primitive, red, green, blue);
    Area_CellAddPrim(slot->pos.x.fixed, slot->pos.y.fixed, 3, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801F3560);
#endif
