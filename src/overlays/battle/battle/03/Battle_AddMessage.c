#include "battle_03.h"

/* func_801DE8C0 */
MATCH void Battle_AddMessage(s8 index, s8 record_type, u8* text) {
    u8 i;

    i                               = D_801EC328;
    g_BattleMessages[i].flags       = index;
    i                               = D_801EC328;
    g_BattleMessages[i].record_type = record_type;
    i                               = D_801EC328;
    g_BattleMessages[i].text        = text;
    D_801EC328                      = (i + 1u) & 0xFu;
}
