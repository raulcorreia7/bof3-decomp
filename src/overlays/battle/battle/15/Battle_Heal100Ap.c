#include "battle_15.h"

/* func_8009E224 */
MATCH void Battle_Heal100Ap(void) {
    g_Battle.target_record->target_flags = 2;
    g_Battle.target_record->ap_change    = -0x64;
}
