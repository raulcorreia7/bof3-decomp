#include "battle_03.h"

/* Byte-displacement views over the active-count byte, the local-work array
 * (stride 0x140) and the ability template records (stride 0xA4). */

/* One 16-byte block of a template record; the copy below walks the record in
 * these blocks (the trailing word is copied separately). */
typedef struct BattleTemplateBlock {
    u32 words[4];
} BattleTemplateBlock;

MATCH void func_801DD08C(void) {
    u8 index;

    index = 0u;
    while (index < VOL(u8, g_BattlePartyCount)) {
        u32                  work_offset;
        u8                   template_index;
        BattleTemplateBlock* src;
        BattleTemplateBlock* dst;
        BattleTemplateBlock* end;

        work_offset    = index * 0x140u;
        template_index = g_BattlePartyBattlers[index].record_slot;
        src            = (BattleTemplateBlock*)(&g_Characters[template_index]);
        dst            = (BattleTemplateBlock*)(D_80145F04 + work_offset);
        end            = src + 10;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        *(u32*)dst = *(u32*)src;
        /* FAKE: MATCH_BARRIER holds the trailing-word copy before the increment;
         * without it the load-delay nop slot is filled by the increment. */
        MATCH_BARRIER();
        index++;
    }
}
