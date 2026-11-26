#include "area189_13.h"

#include <inline_c.h>

/* Draws the visible band of the map: the two per-buffer lists of every grid row are emptied, then
 * each cell of the rotated 56 x 28 band is projected, culled against the screen box, textured, and
 * linked into the list its row and the draw buffer select. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F2DE0(void) {
    u8*       base;
    u8*       next;
    s8*       rec;
    u32       level;
    u32       address;
    u32       row_offset;
    u32       column_offset;
    u32       slot_offset;
    u32       offset;
    s32       row;
    s32       col;
    s32       angle;
    s32       orientation;
    s32       side;
    s32       x;
    s32       y;
    s32       cell_index;
    u32       texture;
    u16       cell;
    u16       ux;
    u16       uy;
    u8        block;
    u16       slot;
    POLY_FT4* prim;

    row                   = 0;
    base                  = (u8*)&D_80142CC0;
    level                 = g_GfxBufferIndex;
    row_offset            = 0;
    g_AreaCellPacketCount = 0;
    do {
        col           = 0;
        offset        = row_offset;
        column_offset = level;
        do {
            address = column_offset << 3;
            col++;
            slot_offset                       = address + offset;
            address                           = address + base;
            *(u32*)(D_80142CC4 + slot_offset) = offset + address;
            *(u32*)(D_80142CC0 + slot_offset) = 0;
            column_offset += 2;
        } while (col < 2);
        row++;
        row_offset += 0x30;
    } while (row < AREA_CELL_GRID_ROWS);

    angle       = (g_AreaCameraAngle.vz + 0x100) >> 9;
    orientation = angle & 7;
    side        = (angle & 1) ^ 1;

    x                            = (s8)D_801F6108[orientation * 6] - (((((u32)g_AreaCameraX >> 8) + 0x80) & 0xFF) - 0x100);
    g_ScratchPad.cells.halves[0] = x;
    g_AreaTileOriginX            = x;
    y                            = (s8)D_801F6108[orientation * 6 + 3] - (((((u32)g_AreaCameraY >> 8) + 0x80) & 0xFF) - 0x100);
    g_ScratchPad.cells.words[2]  = side * 12 + AREA_CELL_GRID_COLS;
    g_ScratchPad.cells.words[1]  = AREA_CELL_GRID_ROWS - side * 12;
    g_AreaCellPrimFreeIndex      = 0;
    g_ScratchPad.cells.halves[1] = y;
    g_AreaTileOriginY            = y;

    for (row = 0; row < g_ScratchPad.cells.words[1]; row++) {
        for (col = 0; col < g_ScratchPad.cells.words[2]; col++) {
            if ((u32)g_AreaCellPrimFreeIndex >= 0x400) {
                continue;
            }

            x = g_ScratchPad.cells.halves[0] + col * (s8)D_801F6108[orientation * 6 + 1] + row * (s8)D_801F6108[orientation * 6 + 2] / 2;
            y = g_ScratchPad.cells.halves[1] + col * (s8)D_801F6108[orientation * 6 + 4] + (row + 1) * (s8)D_801F6108[orientation * 6 + 5] / 2;

            block                     = D_801F6138[(y & 0xF0) | ((x & 0xF0) >> 4)];
            g_ScratchPadVectors[0].vx = (x << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
            g_ScratchPadVectors[0].vy = (y << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
            cell_index                = ((block & 0xF0) | (y & 0xF)) * 0x60 + (((block & 0xF) << 4) | (x & 0xF));
            D_1F800010                = (s8*)(MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + cell_index * 4);
            g_ScratchPadVectors[0].vz = -(D_1F800010[0] << 4);
            gte_ldv0(&g_ScratchPadVectors[0]);
            gte_rtps();
            gte_stsxy(&D_1F800034[0]);

            if ((s16)D_1F800034[1] < 0x79) {
                if ((u16)(D_1F800034[0] + 0x31) >= 0x1A3) {
                    continue;
                }
            } else if ((u16)(D_1F800034[0] + 0xC7) >= 0x2CF) {
                continue;
            }

            cell    = MEM(u16, MAP_BUNDLE_BASE + g_AreaMapBundle.grid_offset * 4 + cell_index * 2);
            texture = MEM(u32, MAP_BUNDLE_BASE + g_AreaMapBundle.grid_offset * 4 + ((g_AreaMapBundle.width * g_AreaMapBundle.height + 1) / 2) * 4 + cell * 4);

            slot                    = g_AreaCellPrimFreeIndex;
            g_AreaCellPrimFreeIndex = slot + 1;
            Area_CellSetTexture(texture, &g_AreaCellPrims[slot][g_GfxBufferIndex]);

            prim                      = &g_AreaCellPrims[slot][g_GfxBufferIndex];
            *(u32*)&prim->x0          = *(u32*)D_1F800034;
            ux                        = g_ScratchPadVectors[0].vx;
            uy                        = g_ScratchPadVectors[0].vy;
            rec                       = D_1F800010;
            /* The other three corners of the cell, one half cell over. */
            g_ScratchPadVectors[1].vx = ux + 0x80;
            g_ScratchPadVectors[1].vy = uy;
            g_ScratchPadVectors[1].vz = -(rec[0] << 4);
            g_ScratchPadVectors[2].vx = ux;
            g_ScratchPadVectors[2].vy = uy + 0x80;
            g_ScratchPadVectors[2].vz = -(rec[2] << 4);
            g_ScratchPadVectors[3].vx = ux + 0x80;
            g_ScratchPadVectors[3].vy = uy + 0x80;
            g_ScratchPadVectors[3].vz = -(rec[3] << 4);
            gte_ldv3c(&g_ScratchPadVectors[1]);
            gte_rtpt();

            offset = (AREA_CELL_GRID_ROWS - 1 - row) * 0x30 + g_GfxBufferIndex * 8;
            next   = *(u8**)(D_80142CC4 + offset);
            setaddr(next, prim);
            *(u8**)(D_80142CC4 + offset) = (u8*)prim;
            gte_stsxy3(&prim->x1, &prim->x2, &prim->x3);
        }
    }
}
#else
INCLUDE_ASM(func_801F2DE0);
#endif
