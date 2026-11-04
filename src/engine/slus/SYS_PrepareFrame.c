#include "engine/slus/slus.h"

/* rebuilds the active boot-frame ordering-table and packet-pointer
 * tables, then restores the two fixed packet arena bounds.
 */
MATCH void SYS_PrepareFrame(void) {
    u8*  packet;
    u32* ordering;
    u8   buffer_index;
    u32  packet_offset;
    u32  table_offset;
    s32  index;

    index           = 0;
    ordering        = (u32*)D_801459D0;
    buffer_index    = g_FrameBufferIndex;
    packet          = D_80145990;
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

    index         = 0;
    buffer_index  = g_FrameBufferIndex;
    packet        = D_80142CE0;
    packet_offset = buffer_index << 3;
    table_offset  = (buffer_index + 4) << 3;
    do {
        *(u32*)(D_80142CC0 + table_offset) = 0;
        *(u32*)(D_80142CC4 + table_offset) = (u32)(packet + packet_offset);
        packet += 0x30;
        table_offset += 0x30;
        index++;
    } while (index < 56);

    D_801459F8 = (void*)AREA_WORK_WINDOW;
    D_801459FC = AREA_CODE_BASE;
}
