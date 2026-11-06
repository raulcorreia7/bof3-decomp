#include "start_08.h"

/* The block at D_801448D8 holds the 0xA4-byte Character party records
 * at +0x90 (g_SaveData.characters). */
typedef struct StartPartyBlock {
    u8        unk_00[0x90];
    Character records[8];
} StartPartyBlock;

/* Per-character willpower divisor and base pair. */

/* D_801448D8 spelled from g_SaveData.characters so the block base stays one symbol. */
#define START_PARTY ((StartPartyBlock*)((u8*)g_SaveData.characters - 0x90))
#define RECORDS     (g_SaveData.characters)

MATCH void Party_InitDefaults(void) {
    u8 index;
    u8 willpower;

    for (index = 0; index < 7; index++) {
        RECORDS[index] = D_801EB514[index];
        willpower      = (g_SaveData.characters[index].level << 4) / D_801EBA34[index][0] + D_801EBA34[index][1];
        START_PARTY->records[index].base.willpower   = willpower;
        START_PARTY->records[index].willpower        = willpower;
        g_SaveData.characters[index].stats.willpower = willpower;
    }
    RECORDS[D_80181B1A] = D_801EB990;
}
