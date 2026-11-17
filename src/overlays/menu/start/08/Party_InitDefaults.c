#include "start_08.h"

/* D_801448D8 spelled from g_Characters so the block base stays one symbol. */
#define START_PARTY ((SaveData*)((u8*)g_Characters - DECOMP_OFFSETOF(SaveData, characters)))
#define RECORDS     (g_Characters)

MATCH void Party_InitDefaults(void) {
    u8 index;
    u8 willpower;

    for (index = 0; index < CHAR_INDEX_WHELP; index++) {
        RECORDS[index]                                = g_NewGameCharacters[index];
        willpower                                     = (g_Characters[index].level << 4) / g_NewGameWillpowerCurves[index].level_divisor + g_NewGameWillpowerCurves[index].base;
        START_PARTY->characters[index].base.willpower = willpower;
        START_PARTY->characters[index].willpower      = willpower;
        g_Characters[index].stats.willpower           = willpower;
    }
    RECORDS[D_80181B1A] = g_NewGameCharacters[CHAR_INDEX_WHELP];
}
