#include "engine/slus/slus.h"

/* One 8-byte move entry. The u16 flags field overlaps the high half of the
 * control word, so the views share a union. */
typedef union MoveEntry {
    u32 control;

    struct {
        u16 unk_00;
        u16 flags;
    } wide;

    struct {
        u8 pad_00[3];
        u8 index;
        u8 y;
        u8 x;
        u8 h;
        u8 w;
    } bytes;
} MoveEntry;

/* Draws the record's selected move entry as a display rectangle and queues the primitive.
 */
MATCH void func_80158830(void* obj) {
    RECT       rect;
    MoveEntry* entry;
    u32        control;
    u32        dividend;
    u32        divisor;
    u32        rem;
    s16        x_part;
    u8*        base;
    u32        index;

    base = obj;
    if ((Area_TestCondition(*(s16*)(base + 4)) << 0x18) != 0) {
        dividend = g_FrameCount;
        divisor  = base[0] + 1;
        rem      = dividend % divisor;
        index    = 2;
        /* The constant-true loop test and the doubled break reproduce the retail scan branch layout. */
        for (; 2 != 0; index += 2) {
            entry = (MoveEntry*)(base + (index << 2));
            if (entry->bytes.index >= (s32)rem) {
                if (entry->bytes.index) {
                    break;
                } else {
                    break;
                }
            }
        }
        entry  = (MoveEntry*)((index << 2) + (u32)base);
        x_part = ((entry->wide.flags & 0xF) << 7) + SCREEN_WIDTH;
        rect.x = entry->bytes.x;
        setRECT(&rect, x_part + (rect.x >> 1), entry->bytes.y + 256, entry->bytes.w, entry->bytes.h + 1);
        control = entry->control;
        SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, (((entry->control >> 0xD) & 0x780) + SCREEN_WIDTH) + ((control >> 9) & 0x7F), (entry->control & BYTE_MASK) | 0x100);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));
    }
}
