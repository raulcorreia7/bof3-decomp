#include "engine/slus/slus.h"

/* copies the matching eight-byte selection record into the active
 * scratch work record, including its paired palette bytes; returns true
 * when the table has no matching id.
 */
/* FAKE: retail accesses the word at +0x70 whole; the member is the byte the entity rows use. */
/* func_8014DD3C */
MATCH bool Area_FindSceneRecord(s32 wanted_id) {
    s32 i;
    u16 id;
    u32 mask;
    u8* count_ptr;
    /* FAKE: empty frame allocation. */
    u8  scratch[8];
    s32 palette_offset;
    u8* unused;
    s32 count;

    unused = scratch;
    i      = 0;
    count  = (s32)D_800E3800;
    if (count > 0) {
        wanted_id &= HALF_MASK;
        mask      = ~0xFF;
        count_ptr = (u8*)SCENE_TABLE_BASE;
        do {
            id = *(u16*)(D_801459F4 + i * 8);
            if (id == wanted_id) {
                g_SpadWork->unk_25 = D_801459F4[i * 8 + 4];
                g_SpadWork->unk_26 = D_801459F4[i * 8 + 5];
                g_SpadWork->unk_27 = *(u16*)(D_801459F4 + i * 8 + 2);
                palette_offset     = id * 2;
                g_SpadWork->unk_28 = D_801459F4[i * 8 + 6];
                g_SpadWork->unk_2C = D_801459F4[i * 8 + 7];
                g_SpadWork->state_70.word &= mask;
                /* FAKE: non-const byte view of the flag table; a const read lets the address loads fold. */
                g_SpadWork->state_70.word = ((u8*)D_80181484)[palette_offset];
                g_SpadWork->unk_2B        = ((u8*)D_80181484)[palette_offset + 1];
                return false;
            }
            i++;
        } while (i < (s32)*count_ptr);
    }
    return true;
}
