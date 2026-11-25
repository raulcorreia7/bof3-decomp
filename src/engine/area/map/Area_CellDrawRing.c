#include "engine/slus/slus.h"

#include <inline_c.h>

#define SCRATCH_AT(type, off)       ((type*)((u8*)&g_ScratchPad + (off)))
#define SCRATCH(type, off)          (*SCRATCH_AT(type, off))

/* Appends the packet to a list of the cell ordering table. */
#define LINK_PACKET(row, list, pkt) (setaddr(g_AreaCellPacketLists[row][list].tail, pkt), g_AreaCellPacketLists[row][list].tail = (P_TAG*)(pkt))

/* Draws the visible window of the 0x37 by 0x1C tile ring: each cell is projected through the GTE, culled against the
 * screen box, given a packet pair (plus linked rows at +0x46/+0x4E) and linked into the ordering table by depth.
 * The scratch words behind SCRATCH(s32, 0xC) hold the window half-width.
 */
/* func_801530D0 */
#ifdef NON_MATCHING
NON_MATCHING s32 Area_CellDrawRing(void) {
    s32       grid_row;
    s32       origin_x;
    s32       next_row;
    s32       next_col;
    s32       window;
    s32       wrapped;
    s32       tilt;
    s32       ring;
    s32       inner;
    s32       outer;
    s32       origin_y;
    s32       depth_threshold;
    u8*       map_width_ptr;
    s8*       rec;
    s32       width;
    s32       v;
    s32       tmp;
    s32       col;
    s32       fp;
    s32       s6;
    s32       s2;
    u16       v16;
    u8        low;
    u32       word;
    AreaCell* cell;
    POLY_FT4* prim;
    POLY_FT4* pkt;
    POLY_FT4* pkt2;
    POLY_FT4* link;
    s32       x;
    u16       ux;
    u16       uy;
    s32       y;
    s32       ring_cell;
    s32       sword;
    s8*       below;
    u8*       low_min;

    Area_CellResetPacketLists();
    tilt                  = g_AreaCameraAngle.vz - 0x200;
    tilt                  = ABS(tilt);
    origin_x              = g_AreaTileOriginX;
    origin_y              = g_AreaTileOriginY;
    g_AreaCellPacketCount = 0;
    D_8014933A &= 0xFE;
    ring              = (0x160 - tilt) / 50;
    SCRATCH(s32, 0xC) = ring;
    depth_threshold   = (g_AreaTargetCellX - origin_x) + (g_AreaTargetCellY - origin_y) + 8;
    width             = 0;
    if (ring > 0) {
        width = ring - 1;
    }
    SCRATCH(s32, 0xC) = width;
    ring_cell         = (s16)g_AreaCameraOffsetZ / 650;
    inner             = 0;
    if (width >= (s16)ring_cell) {
        inner = width - (s16)ring_cell;
    }
    SCRATCH(s32, 0xC) = inner;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
        outer = 0;
        if (inner >= 2) {
            outer = inner - 2;
        }
        SCRATCH(s32, 0xC) = outer;
    }
    s6 = 0;
    if (g_AreaSceneMode == 0x23) {
        SCRATCH(s32, 0xC) = 0;
    }
    map_width_ptr = MEM_PTR(u8, MAP_BUNDLE_BASE);
    grid_row      = g_AreaGridRowCursor;
    D_80149341    = SCRATCH(s32, 0xC);
    low_min       = SCRATCH_AT(u8, 0);
    do {
        next_row = 0;
        if (grid_row != 0x37) {
            next_row = grid_row + 1;
        }
        window   = SCRATCH(s32, 0xC);
        grid_row = next_row;
        col      = g_AreaGridColCursor + window;
        wrapped  = col;
        if (col >= 28) {
            wrapped = col - 28;
        }
        col = wrapped;
        fp  = 0;
        if ((0x1C - (window * 2)) > 0) {
            do {
                next_col = 0;
                if (col != 27) {
                    next_col = col + 1;
                }
                col  = next_col;
                cell = &g_AreaCells[grid_row][col];
                if ((cell->tile_x == 0) || (cell->tile_y == 0)) {
                    Area_CellReleasePrims(cell);
                    D_8014933A |= 1;
                } else {
                    g_ScratchPadVectors[0].vx   = (cell->tile_x << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
                    g_ScratchPadVectors[0].vy   = (cell->tile_y << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
                    rec        = (s8*)((MAP_BUNDLE_BASE + 0x30) + cell->tile_y * *map_width_ptr * 4 + cell->tile_x * 4);
                    D_1F800010 = rec;
                    g_ScratchPadVectors[0].vz   = -(rec[0] * 0x10);
                    gte_ldv0(&g_ScratchPadVectors[0]);
                    gte_rtps();
                    gte_stsxy(&D_1F800034[0]);
                    if (((u16)(D_1F800034[0] + 0x32) >= 0x1A5U) || ((u16)(D_1F800034[1] + 0xC8) >= 0x1EBU)) {
                        Area_CellReleasePrims(cell);
                    } else {
                        s2 = cell->prim_slot & AREA_CELL_PRIM_MASK;
                        if (s2 != 0) {
                            prim = g_AreaCellPrims[s2];
                            v16  = prim[0].pad1;
                            if (v16 != 0) {
                                Area_CellUpload(cell->tile_x, cell->tile_y, prim, v16 - 1);
                                prim[0].pad1 = 0;
                            }
                            goto block_38;
                        }
                        v16             = Area_CellAllocPrimSlot();
                        s2              = v16;
                        cell->prim_slot = v16;
                        if (s2 != 0) {
                            rec   = D_1F800010;
                            prim  = g_AreaCellPrims[s2];
                            sword = *(s32*)rec;
                            if (((rec[4] < ((sword << 0x10) >> 0x18)) | (rec[6] < (sword >> 0x18))) != 0) {
                                prim[1].pad1 = Area_CellAllocPrimSlot();
                            }
                            rec   = D_1F800010;
                            sword = *(s32*)rec;
                            below = rec + *map_width_ptr * 4;
                            if (((below[0] < ((sword << 8) >> 0x18)) | (((*(s32*)below << 0x10) >> 0x18) < (sword >> 0x18))) != 0) {
                                prim[1].pad2 = Area_CellAllocPrimSlot();
                            }
                            cell->prim_slot |= Area_CellUpload(cell->tile_x, cell->tile_y, prim, g_GfxBufferIndex);
                            v = 1;
                            if (g_GfxBufferIndex == 0) {
                                v = 2;
                            }
                            prim[0].pad1 = v;
                        block_38:
                            pkt                        = &prim[g_GfxBufferIndex];
                            *(u32*)&pkt->x0            = *(u32*)D_1F800034;
                            ux                         = g_ScratchPadVectors[0].vx;
                            uy                         = g_ScratchPadVectors[0].vy;
                            rec                        = D_1F800010;
                            g_ScratchPad.vectors[1].vx = ux + 0x80;
                            g_ScratchPad.vectors[2].vx = ux;
                            setVector(&g_ScratchPad.vectors[3], ux + 0x80, uy + 0x80, -(rec[3] * 0x10));
                            g_ScratchPad.vectors[1].vy = uy;
                            g_ScratchPad.vectors[2].vy = uy + 0x80;
                            g_ScratchPad.vectors[1].vz = -(((*(s32*)rec << 0x10) >> 0x18) * 0x10);
                            g_ScratchPad.vectors[2].vz = -(rec[2] * 0x10);
                            gte_ldv3c(&g_ScratchPad.vectors[1]);
                            pkt2 = &g_AreaCellPrims[s2][g_GfxBufferIndex];
                            gte_rtpt();
                            if (cell->prim_slot & 0x8000) {
                                if (cell->prim_slot & 0x4000) {
                                    LINK_PACKET((s6 != 0) ? s6 - 1 : 0, g_GfxBufferIndex, pkt);
                                } else {
                                    LINK_PACKET(s6, g_GfxBufferIndex + 2, pkt);
                                }
                            } else if ((cell->prim_slot & 0x4000) && ((g_AreaDrawMode == GFX_LAYER_FIELD_SCENE) || ((g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) && (depth_threshold < s6)))) {
                                *low_min = *(u32*)rec ^ 0x80;
                                word     = *(u32*)rec >> 8;
                                if (((word & BYTE_MASK) ^ 0x80) < *low_min) {
                                    *low_min = word ^ 0x80;
                                }
                                rec = D_1F800010;
                                v16 = *(u16*)(rec + 2);
                                if (((v16 & BYTE_MASK) ^ 0x80) < *low_min) {
                                    *low_min = v16 ^ 0x80;
                                }
                                low = rec[3];
                                if ((low ^ 0x80) < *low_min) {
                                    *low_min = low ^ 0x80;
                                }
                                tmp = g_AreaCellPacketCount;
                                g_AreaCellPacketCount += 1;
                                g_AreaCellPackets[tmp] = (s6 << 0x18) | (cell->prim_slot & AREA_CELL_PRIM_MASK) | (*low_min << 0x10);
                            } else {
                                LINK_PACKET(s6, g_GfxBufferIndex, &prim[g_GfxBufferIndex]);
                            }
                            gte_stsxy3((s32*)&prim[g_GfxBufferIndex].x1, (s32*)&prim[g_GfxBufferIndex].x2, (s32*)&prim[g_GfxBufferIndex].x3);
                            v16 = g_AreaCellPrims[s2][1].pad1;
                            if (v16 != 0) {
                                link             = &g_AreaCellPrims[v16][g_GfxBufferIndex];
                                *(u32*)&link->x0 = *(u32*)&pkt2->x3;
                                *(u32*)&link->x1 = *(u32*)&pkt2->x1;
                                x                = (cell->tile_x << 7) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
                                g_ScratchPadVectors[0].vx       = x;
                                y                = (cell->tile_y - 0x80) << 7;
                                g_ScratchPadVectors[0].vy       = y - AREA_CELL_HALF;
                                rec              = (s8*)((MAP_BUNDLE_BASE + 0x34) + cell->tile_y * g_AreaMapBundle.width * 4 + cell->tile_x * 4);
                                D_1F800010       = rec;
                                g_ScratchPadVectors[1].vx       = x;
                                g_ScratchPadVectors[1].vy       = y + AREA_CELL_HALF;
                                g_ScratchPadVectors[0].vz       = -(rec[0] * 0x10);
                                g_ScratchPadVectors[1].vz       = -((s8) * (u16*)(rec + 2) * 0x10);
                                gte_ldv3c(&g_ScratchPadVectors[0]);
                                LINK_PACKET(s6, g_GfxBufferIndex + (((cell->prim_slot >> 0xC) & 2) ^ 2), link);
                                gte_rtpt();
                                gte_stsxy3((s32*)&link->x3, (s32*)&link->x2, (s32*)D_1F800034);
                            }
                            v16 = g_AreaCellPrims[s2][1].pad2;
                            if (v16 != 0) {
                                link                       = &g_AreaCellPrims[v16][g_GfxBufferIndex];
                                *(u32*)&link->x0           = *(u32*)&pkt2->x2;
                                *(u32*)&link->x1           = *(u32*)&pkt2->x3;
                                x                          = (cell->tile_x - 0x80) << 7;
                                g_ScratchPadVectors[0].vx                 = x - AREA_CELL_HALF;
                                y                          = (cell->tile_y << 7) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
                                g_ScratchPadVectors[0].vy                 = y;
                                rec                        = (s8*)((MAP_BUNDLE_BASE + 0x30) + (cell->tile_y + 1) * g_AreaMapBundle.width * 4 + cell->tile_x * 4);
                                D_1F800010                 = rec;
                                g_ScratchPadVectors[1].vx                 = x + AREA_CELL_HALF;
                                g_ScratchPad.vectors[1].vy = y;
                                g_ScratchPadVectors[0].vz                 = -(rec[0] * 0x10);
                                g_ScratchPad.vectors[1].vz = -(((*(s32*)rec << 0x10) >> 0x18) * 0x10);
                                gte_ldv3c(&g_ScratchPadVectors[0]);
                                LINK_PACKET(s6, g_GfxBufferIndex + (((cell->prim_slot >> 0xB) & 2) ^ 2), link);
                                gte_rtpt();
                                gte_stsxy3((s32*)&link->x2, (s32*)&link->x3, (s32*)D_1F800034);
                            }
                        }
                    }
                }
                fp += 1;
            } while (fp < (0x1C - (SCRATCH(s32, 0xC) * 2)));
        }
        s6 += 1;
    } while (s6 < 0x37);
    Area_CellSortPackets();
}
#else
INCLUDE_ASM(Area_CellDrawRing);
#endif
