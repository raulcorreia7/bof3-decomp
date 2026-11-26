#include "battle_03.h"
#include "common/copy.h"

/* Byte-displacement views over the active-count byte, the local-work array
 * (stride 0x140) and the ability template records (stride 0xA4). */

MATCH void func_801DD08C(void) {
    u8 index;

    index = 0u;
    while (index < g_Battle.party_count) {
        u32    work_offset;
        u8     template_index;
        Cpy16* src;
        Cpy16* dst;
        Cpy16* end;

        work_offset    = index * 0x140u;
        template_index = g_Game.members[index].character_index;
        src            = (Cpy16*)(&g_Characters[template_index]);
        dst            = (Cpy16*)(g_Game.members[0].chr.name + work_offset);
        end            = src + 10;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        *(u32*)dst = *(u32*)src;
        /* FAKE: FAKE_BARRIER holds the trailing-word copy before the increment;
         * without it the load-delay nop slot is filled by the increment. */
        FAKE_BARRIER();
        index++;
    }
}
