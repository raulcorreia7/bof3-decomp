#include "engine/slus/slus.h"

/* links the active frame's eight ordering-table heads to their
 * packet chains with the PsyQ AddPrims helper.
 */
MATCH void SYS_SubmitFrame(void) {
    s32   index;
    u32** ordering_table;
    u8*   packet;
    s32   work_offset;

    index          = 0;
    ordering_table = D_801459D0;
    packet         = D_80145990;
    work_offset    = 0x70;
    do {
        AddPrims(g_GfxCurrentDisplayFrame + work_offset, (void*)(((u32)g_FrameBufferIndex << 5) + (u32)packet),
                 *ordering_table);
        ordering_table++;
        index++;
        packet += 4;
        work_offset += 4;
    } while (index < 8);
}
