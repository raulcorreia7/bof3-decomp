#include "engine/slus/slus.h"

/* packs the work record's texture-page and CLUT selector into the 16-bit word the caller stores: page base
 * 0x1E0/0x1F0 (bit 0x04 of work byte 0x24) plus the page from byte 0x27 shifted up six, and the sub-page bits from
 * byte 0x28's kind.
 */
MATCH void Area_BuildClut(u16* dst) {
    s32 base;
    u32 sel;

    base = ((g_Task->active_flags & 4) != 0) ? 0x1F0 : 0x1E0;
    switch (g_Task->unk_28) {
        case 0:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 4)) << 6) | (sel & 0xF));
            break;
        case 1: {
            u32 n;

            n    = g_Task->unk_27;
            *dst = ((base + n) << 6);
            break;
        }
        case 2:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 3)) << 6) | ((sel & 7) * 2));
            break;
        case 3:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 2)) << 6) | ((sel & 3) * 4));
            break;
        case 4:
        default:
            sel  = g_Task->unk_27;
            *dst = (((base + (sel >> 1)) << 6) | ((sel & 1) * 8));
            break;
    }
}
