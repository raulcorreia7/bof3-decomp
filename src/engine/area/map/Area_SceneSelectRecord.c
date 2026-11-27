#include "engine/slus/slus.h"

/* copies the matching eight-byte selection record into the active
 * scratch work record, including its paired palette bytes; returns true
 * when the table has no matching id.
 */
/* FAKE: retail accesses the word at +0x70 whole; the member is the byte the entity rows use. */
MATCH bool Area_SceneSelectRecord(s32 wanted_id) {
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
    count  = D_800E3800;
    if (count > 0) {
        wanted_id &= HALF_MASK;
        mask      = ~0xFF;
        count_ptr = (u8*)SCENE_TABLE_BASE;
        do {
            id = *(u16*)(g_SceneActorDefs + i * 8);
            if (id == wanted_id) {
                SELF(Actor)->sheet_page   = g_SceneActorDefs[i * 8 + 4];
                SELF(Actor)->sheet_row    = g_SceneActorDefs[i * 8 + 5];
                SELF(Actor)->clut_select  = *(u16*)(g_SceneActorDefs + i * 8 + 2);
                palette_offset            = id * 2;
                SELF(Actor)->palette_8bit = g_SceneActorDefs[i * 8 + 6];
                SELF(Actor)->unk_2C       = g_SceneActorDefs[i * 8 + 7];
                SELF(Actor)->voice_flags.raw &= mask;
                /* FAKE: non-const byte view of the flag table; a const read lets the address loads fold. */
                SELF(Actor)->voice_flags.raw = ((u8*)g_SceneFlagPairs)[palette_offset];
                SELF(Actor)->unk_2B          = ((u8*)g_SceneFlagPairs)[palette_offset + 1];
                return false;
            }
            i++;
        } while (i < *count_ptr);
    }
    return true;
}
