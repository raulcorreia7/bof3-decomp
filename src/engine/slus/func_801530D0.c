#include "engine/slus/slus.h"

#include <inline_c.h>

#define PAD_AT(type, off) ((type*)((u8*)&D_1F800000 + (off)))
#define PAD(type, off)    (*PAD_AT(type, off))

/* Links the packet at pkt into the ordering table slot at byte offset off, as the table's new head. */
#define LINK_PACKET(off, pkt)                                                     \
    do {                                                                          \
        u32* head_                  = *(u32**)&D_80142CC4[off];                   \
        *head_                      = (*head_ & 0xFF000000) | ((u32)(pkt)&0xFFFFFF); \
        *(u32*)&D_80142CC4[off]     = (u32)(pkt);                                 \
    } while (0)

/* Draws the visible window of the 0x37 by 0x1C tile ring: each cell is projected through the GTE, culled against the
 * screen box, given a packet pair (plus linked rows at +0x46/+0x4E) and linked into the ordering table by depth.
 * The scratch words behind PAD(s32, 0xC) hold the window half-width.
 */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801530D0(void) {
    s32 sp10_row;
    s32 origin_x;
    s32 next_row;
    s32 next_col;
    s32 window;
    s32 wrapped;
    s32 tilt;
    s32 ring;
    s32 inner;
    s32 outer;
    s32 origin_y;
    s32 depth_threshold;
    u8* map_width_ptr;
    s32 row_depth_off;
    s32 col_depth_off;
    s8* rec;
    s32 width;
    s32 v;
    s32 tmp;
    s32 row;
    s32 col;
    s32 col_count;
    s32 cell;
    s32 fp;
    s32 s5;
    s32 s6;
    s32 s2;
    u8* s0;
    u8* s1;
    u8* pkt;
    u8* pkt2;
    u8* link;
    u16 v16;
    u16 flags;
    u8  low;
    u32 word;
    s32 sword;
    s8* below;
    u32* head;
    s32 cell2;
    u8* low_min;
    SVECTOR* vert;

    func_80153CC4();
    tilt       = g_AreaCameraAngle.vz - 0x200;
    tilt       = ABS(tilt);
    origin_x   = g_AreaTileOriginX;
    origin_y   = g_AreaTileOriginY;
    D_8014933D = 0;
    D_8014933A &= 0xFE;
    ring            = (0x160 - tilt) / 50;
    PAD(s32, 0xC)   = ring;
    depth_threshold = (g_AreaTargetCellX - origin_x) + (g_AreaTargetCellY - origin_y) + 8;
    width           = 0;
    if (ring > 0) {
        width = ring - 1;
    }
    PAD(s32, 0xC) = width;
    cell          = (s16)g_AreaCameraOffsetZ / 650;
    inner         = 0;
    if (width >= (s16)cell) {
        inner = width - (s16)cell;
    }
    PAD(s32, 0xC) = inner;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
        outer = 0;
        if (inner >= 2) {
            outer = inner - 2;
        }
        PAD(s32, 0xC) = outer;
    }
    s6 = 0;
    if (g_AreaSceneMode == 0x23) {
        PAD(s32, 0xC) = 0;
    }
    map_width_ptr = MEM_PTR(u8, MAP_BUNDLE_BASE);
    row_depth_off = -0x30;
    sp10_row      = g_AreaGridRowCursor;
    col_depth_off = 0;
    D_80149341    = PAD(s32, 0xC);
    low_min       = PAD_AT(u8, 0);
    vert          = D_1F800014;
    do {
        next_row = 0;
        if (sp10_row != 0x37) {
            next_row = sp10_row + 1;
        }
        window   = PAD(s32, 0xC);
        sp10_row = next_row;
        col      = g_AreaGridColCursor + window;
        wrapped  = col;
        if (col >= 28) {
            wrapped = col - 28;
        }
        col = wrapped;
        fp  = 0;
        if ((0x1C - (window * 2)) > 0) {
            s5 = col_depth_off;
            do {
                next_col = 0;
                if (col != 27) {
                    next_col = col + 1;
                }
                col = next_col;
                s0  = (u8*)&g_AreaCells[sp10_row][col];
                if ((s0[0] == 0) || (s0[1] == 0)) {
                    Area_RequestCellRows((AreaCell*)s0);
                    D_8014933A |= 1;
                } else {
                    vert->vx = (s0[0] << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
                    vert->vy = (s0[1] << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
                    rec                         = (s8*)((MAP_BUNDLE_BASE + 0x30) + s0[1] * *map_width_ptr * 4 + s0[0] * 4);
                    D_1F800010              = rec;
                    vert->vz = -(rec[0] * 0x10);
                    gte_ldv0(&D_1F800014[0]);
                    gte_rtps();
                    gte_stsxy(&D_1F800034[0]);
                    if (((u16)(D_1F800034[0] + 0x32) >= 0x1A5U) || ((u16)(D_1F800034[1] + 0xC8) >= 0x1EBU)) {
                        Area_RequestCellRows((AreaCell*)s0);
                    } else {
                        s2 = *(u16*)(s0 + 2) & 0xFFF;
                        if (s2 != 0) {
                            s1  = (u8*)g_AreaCellPrims + s2 * 0x50;
                            v16 = *(u16*)(s1 + 0x1E);
                            if (v16 != 0) {
                                Area_UploadCell(s0[0], s0[1], s1, v16 - 1);
                                *(u16*)(s1 + 0x1E) = 0;
                            }
                            goto block_38;
                        }
                        v16             = Area_AllocCellPrimRow();
                        s2              = v16;
                        *(u16*)(s0 + 2) = v16;
                        if (s2 != 0) {
                            rec   = D_1F800010;
                            s1    = (u8*)g_AreaCellPrims + s2 * 0x50;
                            sword = *(s32*)rec;
                            if (((rec[4] < ((sword << 0x10) >> 0x18)) | (rec[6] < (sword >> 0x18))) != 0) {
                                *(u16*)(s1 + 0x46) = Area_AllocCellPrimRow();
                            }
                            rec   = D_1F800010;
                            sword = *(s32*)rec;
                            below = rec + *map_width_ptr * 4;
                            if (((below[0] < ((sword << 8) >> 0x18)) | (((*(s32*)below << 0x10) >> 0x18) < (sword >> 0x18))) != 0) {
                                *(u16*)(s1 + 0x4E) = Area_AllocCellPrimRow();
                            }
                            *(u16*)(s0 + 2) |= Area_UploadCell(s0[0], s0[1], s1, g_FrameBufferIndex);
                            v = 1;
                            if (g_FrameBufferIndex == 0) {
                                v = 2;
                            }
                            *(s16*)(s1 + 0x1E) = v;
                        block_38:
                            tmp                         = g_FrameBufferIndex * 0x28;
                            pkt                         = tmp + s1;
                            *(u32*)(pkt + 8)            = *(u32*)D_1F800034;
                            rec                         = D_1F800010;
                            D_1F80001C.vx = D_1F800014[0].vx + 0x80;
                            D_1F80001C.vy = D_1F800014[0].vy;
                            D_1F800024.vx = D_1F800014[0].vx;
                            D_1F800024.vy = D_1F800014[0].vy + 0x80;
                            D_1F80001C.vz = -(((*(s32*)rec << 0x10) >> 0x18) * 0x10);
                            D_1F80002C.vx = D_1F800014[0].vx + 0x80;
                            D_1F80002C.vy = D_1F800014[0].vy + 0x80;
                            D_1F800024.vz = -(rec[2] * 0x10);
                            D_1F80002C.vz = -(rec[3] * 0x10);
                            gte_ldv3c(&D_1F80001C);
                            pkt2 = (u8*)g_AreaCellPrims + tmp + s2 * 0x50;
                            gte_rtpt();
                            flags = *(u16*)(s0 + 2);
                            if (flags & 0x8000) {
                                v = g_FrameBufferIndex * 8;
                                if (flags & 0x4000) {
                                    cell = v;
                                    if (s6 != 0) {
                                        cell = v + row_depth_off;
                                    }
                                    head  = *(u32**)&D_80142CC4[cell];
                                    *head = (*head & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                    cell2 = v;
                                    if (s6 != 0) {
                                        cell2 += row_depth_off;
                                    }
                                    *(u32*)&D_80142CC4[cell2] = (u32)pkt;
                                } else {
                                    cell = (g_FrameBufferIndex + 2) * 8 + s5;
                                    LINK_PACKET(cell, pkt);
                                }
                            } else if ((flags & 0x4000) && ((g_AreaDrawMode == 6) || ((g_AreaDrawMode == 4) && (depth_threshold < s6)))) {
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
                                tmp = D_8014933D;
                                D_8014933D += 1;
                                D_80143740[tmp] = (s6 << 0x18) | (*(u16*)(s0 + 2) & 0xFFF) | (*low_min << 0x10);
                            } else {
                                cell = g_FrameBufferIndex * 8 + s5;
                                LINK_PACKET(cell, s1 + g_FrameBufferIndex * 0x28);
                            }
                            gte_stsxy3((s32*)(pkt + 0x10), (s32*)(pkt + 0x18), (s32*)(pkt + 0x20));
                            tmp = s2 * 0x50;
                            v16 = *(u16*)(((u8*)g_AreaCellPrims + 0x46) + tmp);
                            if (v16 != 0) {
                                link                        = (u8*)g_AreaCellPrims + g_FrameBufferIndex * 0x28 + v16 * 0x50;
                                *(u32*)(link + 8)           = *(u32*)(pkt2 + 0x20);
                                *(u32*)(link + 0x10)        = *(u32*)(pkt2 + 0x10);
                                vert[0].vx = (s0[0] << 7) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
                                vert[0].vy = ((s0[1] - 0x80) << 7) - AREA_CELL_HALF;
                                rec                         = (s8*)((MAP_BUNDLE_BASE + 0x34) + s0[1] * g_AreaMapBundle.width * 4 + s0[0] * 4);
                                D_1F800010              = rec;
                                vert[1].vx = vert[0].vx;
                                vert[1].vy = ((s0[1] - 0x80) << 7) + AREA_CELL_HALF;
                                vert[0].vz = -(rec[0] * 0x10);
                                vert[1].vz = -(rec[2] * 0x10);
                                gte_ldv3c(&D_1F800014[0]);
                                cell = (g_FrameBufferIndex + (((*(u16*)(s0 + 2) >> 0xC) & 2) ^ 2)) * 8 + s5;
                                LINK_PACKET(cell, link);
                                gte_rtpt();
                                gte_stsxy3((s32*)(link + 0x20), (s32*)(link + 0x18), (s32*)D_1F800034);
                            }
                            v16 = *(u16*)(((u8*)g_AreaCellPrims + 0x4E) + tmp);
                            if (v16 != 0) {
                                link                        = (u8*)g_AreaCellPrims + g_FrameBufferIndex * 0x28 + v16 * 0x50;
                                *(u32*)(link + 8)           = *(u32*)(pkt2 + 0x18);
                                *(u32*)(link + 0x10)        = *(u32*)(pkt2 + 0x20);
                                vert[0].vx = ((s0[0] - 0x80) << 7) - AREA_CELL_HALF;
                                vert[0].vy = (s0[1] << 7) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
                                rec                         = (s8*)((MAP_BUNDLE_BASE + 0x30) + (s0[1] + 1) * g_AreaMapBundle.width * 4 + s0[0] * 4);
                                D_1F800010              = rec;
                                vert[1].vx = ((s0[0] - 0x80) << 7) + AREA_CELL_HALF;
                                vert[1].vy = vert[0].vy;
                                vert[0].vz = -(rec[0] * 0x10);
                                vert[1].vz = -(rec[1] * 0x10);
                                gte_ldv3c(&D_1F800014[0]);
                                cell = (g_FrameBufferIndex + (((*(u16*)(s0 + 2) >> 0xB) & 2) ^ 2)) * 8 + s5;
                                LINK_PACKET(cell, link);
                                gte_rtpt();
                                gte_stsxy3((s32*)(link + 0x18), (s32*)(link + 0x20), (s32*)D_1F800034);
                            }
                        }
                    }
                }
                fp += 1;
            } while (fp < (0x1C - (PAD(s32, 0xC) * 2)));
        }
        s6 += 1;
        row_depth_off += 0x30;
        col_depth_off += 0x30;
    } while (s6 < 0x37);
    func_80153D34();
}
#else
INCLUDE_ASM(func_801530D0);
#endif
