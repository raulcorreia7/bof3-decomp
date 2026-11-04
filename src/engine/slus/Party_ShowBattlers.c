#include "engine/slus/slus.h"

/* clears bit 6 of the three boot flag bytes.
 */
MATCH void Party_ShowBattlers(void) {
    g_BattlePartyBattlers[0].flags_00 &= ~ACTOR_FLAG_HIDDEN;
    g_BattlePartyBattlers[1].flags_00 &= ~ACTOR_FLAG_HIDDEN;
    g_BattlePartyBattlers[2].flags_00 &= ~ACTOR_FLAG_HIDDEN;
}
