#include "engine/slus/slus.h"

/* links the active frame's eight ordering-table heads to their
 * packet chains with the PsyQ AddPrims helper.
 */
MATCH void SYS_LinkOt(void) {
    s32   index;
    u32** ordering_table;
    u8*   packet;
    s32   work_offset;

    index          = 0;
    ordering_table = g_GfxOtHeads;
    packet         = (u8*)g_GfxLayerLinks;
    work_offset    = 0x70;
    do {
        AddPrims((u_long*)((u8*)g_GfxCurrentBuffer + work_offset), (void*)((g_GfxBufferIndex << 5) + (u32)packet), *ordering_table);
        ordering_table++;
        index++;
        packet += 4;
        work_offset += 4;
    } while (index < 8);
}
