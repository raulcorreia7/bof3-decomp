#include "engine/slus/slus.h"

/* rebuilds the active boot-frame ordering-table and packet-pointer
 * tables, then restores the two fixed packet arena bounds.
 */
MATCH void SYS_PrepareFrame(void) {
    u8*   packet;
    u32** ordering;
    u8    buffer_index;
    s32   index;

    index           = 0;
    ordering        = g_GfxOtHeads;
    buffer_index    = g_GfxBufferIndex;
    packet          = (u8*)g_GfxLayerLinks;
    g_GfxPrimCursor = (u8*)(0x80020000u + ((buffer_index * 9) << 12));
    /* The paired no-op increments keep the counter live across the store; a
     * plain while strength-reduces to a countdown and loses the retail shape. */
    while (index < 8) {
        index++;
        index--;
        *ordering = (buffer_index << 5) + (u32)packet;
        ordering++;
        index++;
        packet += 4;
    }

    index        = 0;
    buffer_index = g_GfxBufferIndex;
    do {
        g_AreaCellPacketLists[index][buffer_index + 4].head = NULL;
        g_AreaCellPacketLists[index][buffer_index + 4].tail = (P_TAG*)&g_AreaCellPacketLists[index][buffer_index + 4];
        index++;
    } while (index < 56);

    g_SysSectorBuffer = (void*)AREA_WORK;
    g_GfxUploadCursor = AREA_CODE_BASE;
}
