#include "area199_13.h"

#define AREA199_TRAIL_PART_WORD ((0x2580u << 16) | 0x8000u)

#ifdef NON_MATCHING
/* Stages each member's walked cells and draws both trail rows at every live cell. */
NON_MATCHING void func_801F3398(void) {
    POLY_FT4* prim;
    POLY_FT4* quad;
    POLY_FT4* below;
    s32       member;
    s32       slot;
    s32       cell;
    s32       i;
    s32       x;

    for (member = 0; member < 2; member++) {
        x = (g_Actors[member + 1].pos.x.fixed + 0x4000) >> 16;
        if (x < D_801F54D0[member * 3 + D_801F44B4[member] * 6]) {
            slot                                  = (D_801F44B4[member] + 1) & 0x1F;
            D_801F54D0[member * 3 + slot * 6]     = x;
            D_801F54D0[member * 3 + slot * 6 + 1] = COORD_INT(g_Actors[member + 1].pos.y);
            D_801F54D0[member * 3 + slot * 6 + 2] = (D_801F54D0[member * 3 + D_801F44B4[member] * 6 + 2] - 1) & 1;
            D_801F44B4[member]                    = slot;
        }

        for (i = 0; i < 0x20; i++) {
            cell = member * 3 + i * 6;
            quad = Area_CellFindQuad(D_801F54D0[cell], D_801F54D0[cell + 1]);
            if (quad == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            *(u32*)&prim->x0 = *(u32*)&quad->x0;
            *(u32*)&prim->x1 = *(u32*)&quad->x1;
            *(u32*)&prim->x2 = *(u32*)&quad->x2;
            *(u32*)&prim->x3 = *(u32*)&quad->x3;
            Area_ApplyTileToQuad(AREA199_TRAIL_PART_WORD + D_801F54D0[cell + 2] + D_801F4544[member * 2], prim, 1);
            Area_CellAddPrim(D_801F54D0[cell] << 16, D_801F54D0[cell + 1] << 16, 0, sizeof(POLY_FT4));

            below = Area_CellFindQuad(D_801F54D0[cell], D_801F54D0[cell + 1] + (s8)D_801F4548[member]);
            if (below == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            *(u32*)&prim->x0 = *(u32*)&below->x0;
            *(u32*)&prim->x1 = *(u32*)&below->x1;
            *(u32*)&prim->x2 = *(u32*)&below->x2;
            *(u32*)&prim->x3 = *(u32*)&below->x3;
            Area_ApplyTileToQuad(AREA199_TRAIL_PART_WORD + D_801F54D0[cell + 2] + D_801F4545[member * 2], prim, 1);
            Area_CellAddPrim(D_801F54D0[cell] << 16, (D_801F54D0[cell + 1] + (s8)D_801F4548[member]) << 16, 0, sizeof(POLY_FT4));
        }
    }
}
#else
INCLUDE_ASM(func_801F3398);
#endif
