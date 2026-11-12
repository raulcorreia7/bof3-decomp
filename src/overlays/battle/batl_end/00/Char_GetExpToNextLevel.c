#include "batl_end_00.h"

/* The exp a party member still needs for the next level; 0 once its exp covers the growth row. */
/* func_801F0BB0 */
MATCH u32 Char_GetExpToNextLevel(s32 slot) {
    u8  index;
    u8  i;
    u32 total;

    total = 0;
    index = func_801DD7AC(g_Game.members[slot & BYTE_MASK].chr.character_id);
    i     = 0;
    while (i <= g_Characters[index].level) {
        total += g_LevelGrowth[index][i].exp;
        i++;
    }
    if (total < g_Characters[index].exp) {
        return 0;
    }
    return total - g_Characters[index].exp;
}
