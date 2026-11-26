#ifndef OVERLAY_BMAGIC_MAGIC080_00_H
#define OVERLAY_BMAGIC_MAGIC080_00_H

/* The bmagic/magic080/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The texture corner of one 12-pixel sprite. */
typedef struct Magic080Cell {
    u16 u;
    u16 v;
} Magic080Cell;

ASSERT_OFFSET(Magic080Cell, v, 0x02);
ASSERT_SIZE(Magic080Cell, 0x04);

extern Magic080Cell D_801EF124[];
extern Magic080Cell D_801EF13C[];

/* Draws COUNT 12-pixel sprites in a row from the effect cell, each textured from its CELLS corner on the page at
 * (960, PAGE_Y). A statement macro: the member declares POLY_FT4* prim and s32 i. */
#define MAGIC080_DRAW_CELLS(COUNT, CELLS, PAGE_Y)                                                                                                                                             \
    for (i = 0; i < COUNT; i++) {                                                                                                                                                             \
        prim = (POLY_FT4*)g_GfxPrimCursor;                                                                                                                                                    \
        SetPolyFT4(prim);                                                                                                                                                                     \
        setXY4(prim, SELF(PartyMember)->screen_x.value + i * 12, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value + (i + 1) * 12, SELF(PartyMember)->screen_y.value,      \
               SELF(PartyMember)->screen_x.value + i * 12, SELF(PartyMember)->screen_y.value + 12, SELF(PartyMember)->screen_x.value + (i + 1) * 12, SELF(PartyMember)->screen_y.value + 12); \
        setRGB0(prim, 0x80, 0x80, 0x80);                                                                                                                                                      \
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x3C0, PAGE_Y);                                                                                                               \
        prim->clut  = GetClut(0, 0x1E0);                                                                                                                                                      \
        setUVWH(prim, CELLS[i].u, CELLS[i].v, 12, 12);                                                                                                                                        \
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));                                                                                                                               \
    }

void func_801EED94(void);

void func_801EEF5C(void);

#endif
