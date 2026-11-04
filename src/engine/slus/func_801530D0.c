#include "engine/slus/slus.h"

#include <inline_c.h>

/* Links the packet at pkt into the ordering table slot at byte offset off, as the table's new head. */
#define LINK_PACKET(off, pkt)                                                          \
    do {                                                                               \
        u32* head_                  = *(u32**)(D_80142CC4 + (off));                    \
        *head_                      = (*head_ & 0xFF000000) | ((u32)(pkt) & 0xFFFFFF); \
        *(u32*)(D_80142CC4 + (off)) = (u32)(pkt);                                      \
    } while (0)

/* draws the visible window of the 0x37 by 0x1C tile ring: each cell is projected through the GTE, culled against the
 * screen box, given a packet pair (plus linked rows at +0x46/+0x4E) and linked into the ordering table by depth.
 * Lifted from the first draft; the scratch words behind D_1F80000C hold the window half-width.
 */
/* nonmatching 69.51%: restated from the first draft with byte offsets, gte macros and a link macro. resume: first
 * mismatch of the register assignment and the shared block_38 tail. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801530D0(void) {
    s32 sp10_row;
    s32 sp18;
    u8* sp20;
    s32 sp40;
    s32 sp48;
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

    func_80153CC4(0);
    v = g_AreaCameraAngle.vz - 0x200;
    if (v < 0) {
        v = -v;
    }
    D_8014933D = 0;
    D_8014933A &= 0xFE;
    tmp        = (0x160 - v) / 50;
    D_1F80000C = tmp;
    sp18       = (D_8014930A - g_AreaTileOriginX) + (D_8014930E - g_AreaTileOriginY) + 8;
    width      = 0;
    if (tmp > 0) {
        width = tmp - 1;
    }
    D_1F80000C = width;
    cell       = g_AreaCameraOffsetZ / 650;
    tmp        = 0;
    if (width >= (s16)cell) {
        tmp = width - (s16)cell;
    }
    D_1F80000C = tmp;
    if (g_GameRequestFlags & 1) {
        v = 0;
        if (tmp >= 2) {
            v = tmp - 2;
        }
        D_1F80000C = v;
    }
    s6 = 0;
    if (g_AreaSceneMode == 0x23) {
        D_1F80000C = 0;
    }
    sp20       = &g_AreaMapBundle.width_00;
    sp40       = -0x30;
    sp10_row   = g_AreaGridRowCursor;
    sp48       = 0;
    D_80149341 = D_1F80000C;
    do {
        v = 0;
        if (sp10_row != 0x37) {
            v = sp10_row + 1;
        }
        tmp      = D_1F80000C;
        sp10_row = v;
        col      = g_AreaGridColCursor + tmp;
        if (col >= 28) {
            col -= 0x1C;
        }
        fp = 0;
        if ((0x1C - (tmp * 2)) > 0) {
            s5 = sp48;
            do {
                v = 0;
                if (col != 27) {
                    v = col + 1;
                }
                col = v;
                s0  = (u8*)g_AreaCells + sp10_row * 0x70 + col * 4;
                if ((s0[0] == 0) || (s0[1] == 0)) {
                    Area_RequestCellRows((AreaCell*)s0);
                    D_8014933A |= 1;
                } else {
                    D_1F800014[0].vx           = (s0[0] << 7) - 0x4040;
                    D_1F800014[0].vy           = (s0[1] << 7) - 0x4040;
                    rec                        = (s8*)((MAP_BUNDLE_BASE + 0x30) + s0[1] * *sp20 * 4 + s0[0] * 4);
                    *(s8**)(D_1F800000 + 0x10) = rec;
                    D_1F800014[0].vz           = -(rec[0] * 0x10);
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
                            rec  = *(s8**)(D_1F800000 + 0x10);
                            s1   = (u8*)g_AreaCellPrims + s2 * 0x50;
                            word = *(u32*)rec;
                            if (((rec[4] < ((s32)(word << 0x10) >> 0x18)) | (rec[6] < (s32)(word >> 0x18))) != 0) {
                                *(u16*)(s1 + 0x46) = Area_AllocCellPrimRow();
                            }
                            rec  = *(s8**)(D_1F800000 + 0x10);
                            word = *(u32*)rec;
                            low  = rec[*sp20 * 4];
                            if (((*(s8*)(rec + *sp20 * 4) < ((s32)(word << 8) >> 0x18)) |
                                 (((s32)((s32)low << 0x10) >> 0x18) < (s32)(word >> 0x18))) != 0) {
                                *(u16*)(s1 + 0x4E) = Area_AllocCellPrimRow();
                            }
                            *(u16*)(s0 + 2) |= Area_UploadCell(s0[0], s0[1], s1, g_FrameBufferIndex);
                            *(s16*)(s1 + 0x1E) = (g_FrameBufferIndex == 0) ? 2 : 1;
                        block_38:
                            tmp              = g_FrameBufferIndex * 0x28;
                            pkt              = tmp + s1;
                            *(u32*)(pkt + 8) = *(u32*)D_1F800034;
                            rec              = *(s8**)(D_1F800000 + 0x10);
                            D_1F800014[1].vx = D_1F800014[0].vx + 0x80;
                            D_1F800014[1].vy = D_1F800014[0].vy;
                            D_1F800014[2].vx = D_1F800014[0].vx;
                            D_1F800014[2].vy = D_1F800014[0].vy + 0x80;
                            D_1F800014[1].vz = -(rec[1] * 0x10);
                            D_1F800014[3].vx = D_1F800014[0].vx + 0x80;
                            D_1F800014[3].vy = D_1F800014[0].vy + 0x80;
                            D_1F800014[2].vz = -(rec[2] * 0x10);
                            D_1F800014[3].vz = -(rec[3] * 0x10);
                            gte_ldv3c(&D_1F800014[0]);
                            pkt2 = (u8*)g_AreaCellPrims + tmp + s2 * 0x50;
                            gte_rtpt();
                            flags = *(u16*)(s0 + 2);
                            tmp   = flags & 0x4000;
                            if (flags & 0x8000) {
                                v = g_FrameBufferIndex * 8;
                                if (tmp != 0) {
                                    cell = v;
                                    if (s6 != 0) {
                                        cell = v + sp40;
                                    }
                                    LINK_PACKET(cell, pkt);
                                } else {
                                    LINK_PACKET((g_FrameBufferIndex + 2) * 8 + s5, pkt);
                                }
                            } else if ((tmp != 0) &&
                                       ((g_AreaDrawMode == 6) || ((g_AreaDrawMode == 4) && (sp18 < s6)))) {
                                word          = *(u32*)rec;
                                D_1F800000[0] = word ^ 0x80;
                                if ((((word >> 8) & BYTE_MASK) ^ 0x80) < D_1F800000[0]) {
                                    D_1F800000[0] = (word >> 8) ^ 0x80;
                                }
                                if ((((u8)rec[2]) ^ 0x80) < D_1F800000[0]) {
                                    D_1F800000[0] = ((u8)rec[2]) ^ 0x80;
                                }
                                if ((((u8)rec[3]) ^ 0x80) < D_1F800000[0]) {
                                    D_1F800000[0] = ((u8)rec[3]) ^ 0x80;
                                }
                                tmp = D_8014933D;
                                D_8014933D += 1;
                                D_80143740[tmp] = (s6 << 0x18) | (*(u16*)(s0 + 2) & 0xFFF) | (D_1F800000[0] << 0x10);
                            } else {
                                LINK_PACKET(g_FrameBufferIndex * 8 + s5, s1 + g_FrameBufferIndex * 0x28);
                            }
                            gte_stsxy3((s32*)(pkt + 0x10), (s32*)(pkt + 0x18), (s32*)(pkt + 0x20));
                            tmp = s2 * 0x50;
                            v16 = *(u16*)(((u8*)g_AreaCellPrims + 0x46) + tmp);
                            if (v16 != 0) {
                                link                 = (u8*)g_AreaCellPrims + g_FrameBufferIndex * 0x28 + v16 * 0x50;
                                *(u32*)(link + 8)    = *(u32*)(pkt2 + 0x20);
                                *(u32*)(link + 0x10) = *(u32*)(pkt2 + 0x10);
                                D_1F800014[0].vx     = (s0[0] << 7) - 0x3FC0;
                                D_1F800014[0].vy     = ((s0[1] - 0x80) << 7) - 0x40;
                                rec =
                                    (s8*)((MAP_BUNDLE_BASE + 0x34) + s0[1] * g_AreaMapBundle.width_00 * 4 + s0[0] * 4);
                                *(s8**)(D_1F800000 + 0x10) = rec;
                                D_1F800014[1].vx           = D_1F800014[0].vx;
                                D_1F800014[1].vy           = ((s0[1] - 0x80) << 7) + 0x40;
                                D_1F800014[0].vz           = -(rec[0] * 0x10);
                                D_1F800014[1].vz           = -(rec[2] * 0x10);
                                gte_ldv3c(&D_1F800014[0]);
                                LINK_PACKET((g_FrameBufferIndex + (((*(u16*)(s0 + 2) >> 0xC) & 2) ^ 2)) * 8 + s5, link);
                                gte_rtpt();
                                gte_stsxy3((s32*)(link + 0x20), (s32*)(link + 0x18), (s32*)D_1F800034);
                            }
                            v16 = *(u16*)(((u8*)g_AreaCellPrims + 0x4E) + tmp);
                            if (v16 != 0) {
                                link                 = (u8*)g_AreaCellPrims + g_FrameBufferIndex * 0x28 + v16 * 0x50;
                                *(u32*)(link + 8)    = *(u32*)(pkt2 + 0x18);
                                *(u32*)(link + 0x10) = *(u32*)(pkt2 + 0x20);
                                D_1F800014[0].vx     = ((s0[0] - 0x80) << 7) - 0x40;
                                D_1F800014[0].vy     = (s0[1] << 7) - 0x3FC0;
                                rec = (s8*)((MAP_BUNDLE_BASE + 0x30) + (s0[1] + 1) * g_AreaMapBundle.width_00 * 4 +
                                            s0[0] * 4);
                                *(s8**)(D_1F800000 + 0x10) = rec;
                                D_1F800014[1].vx           = ((s0[0] - 0x80) << 7) + 0x40;
                                D_1F800014[1].vy           = D_1F800014[0].vy;
                                D_1F800014[0].vz           = -(rec[0] * 0x10);
                                D_1F800014[1].vz           = -(rec[1] * 0x10);
                                gte_ldv3c(&D_1F800014[0]);
                                LINK_PACKET((g_FrameBufferIndex + (((*(u16*)(s0 + 2) >> 0xB) & 2) ^ 2)) * 8 + s5, link);
                                gte_rtpt();
                                gte_stsxy3((s32*)(link + 0x18), (s32*)(link + 0x20), (s32*)D_1F800034);
                            }
                        }
                    }
                }
                fp += 1;
            } while (fp < (0x1C - (D_1F80000C * 2)));
        }
        s6 += 1;
        sp40 += 0x30;
        sp48 += 0x30;
    } while (s6 < 0x37);
    func_80153D34();
}
#else
INCLUDE_ASM(func_801530D0);
#endif
