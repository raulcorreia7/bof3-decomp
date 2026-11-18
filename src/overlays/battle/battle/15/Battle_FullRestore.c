#include "battle_15.h"

/* func_8009FFB4 */
MATCH void Battle_FullRestore(void) {
    Battle_CureStatus(g_Battle.target, 0xBFC);
    Battle_HealFullHp();
}
