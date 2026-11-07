#include "start_08.h"

/* The block at D_801448D8 holds the 0xA4-byte Character party records
 * at +0x90 (g_Characters). */
typedef struct StartPartyBlock {
    u8        unk_00[0x90];
    Character records[8];
} StartPartyBlock;

/* D_801448D8 spelled from g_Characters so the block base stays one symbol. */
#define START_PARTY ((StartPartyBlock*)((u8*)g_Characters - 0x90))
#define RECORDS     (g_Characters)

MATCH void Party_InitDefaults(void) {
    u8 index;
    u8 willpower;

    for (index = 0; index < 7; index++) {
        RECORDS[index] = g_StartCharacters[index];
        willpower      = (g_Characters[index].level << 4) / g_StartWillpowerCurves[index].level_divisor +
                         g_StartWillpowerCurves[index].base;
        START_PARTY->records[index].base.willpower = willpower;
        START_PARTY->records[index].willpower      = willpower;
        g_Characters[index].stats.willpower        = willpower;
    }
    RECORDS[D_80181B1A] = g_StartCharacters[CHAR_INDEX_WHELP];
}
