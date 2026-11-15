#include "engine/slus/slus.h"

/* packs the work record's texture-page and CLUT selector into the 16-bit word the caller stores: page base
 * 0x1E0/0x1F0 (bit 0x04 of work byte 0x24) plus the page from byte 0x27 shifted up six, and the sub-page bits from
 * byte 0x28's kind.
 */
MATCH void Area_BuildClut(u16* dst) {
    s32 base;
    u32 sel;

    base = ((g_Task->active_flags & 0x4) != 0) ? STAGE_PALETTE_Y + 16 : STAGE_PALETTE_Y;
    switch (g_Task->unk_28) {
        case PALETTE_TYPE_CELL:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 4)) << 6) | (sel & 0xF));
            break;
        case PALETTE_TYPE_ROW: {
            u32 n;

            n    = g_Task->unk_27;
            *dst = ((base + n) << 6);
            break;
        }
        case PALETTE_KIND_CELLS_2:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 3)) << 6) | ((sel & 0x7) * 2));
            break;
        case PALETTE_TYPE_CELLS_4:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 2)) << 6) | ((sel & 0x3) * 4));
            break;
        case PALETTE_TYPE_CELLS_8:
        default:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 0x1)) << 6) | ((sel & 1) * 8));
            break;
    }
}
