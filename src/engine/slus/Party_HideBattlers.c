#include "engine/slus/slus.h"

/* sets bit 6 of the three boot flag bytes.
 */
MATCH void Party_HideBattlers(void) {
    g_BattlePartyBattlers[0].header.flags |= ACTOR_FLAG_HIDDEN;
    g_BattlePartyBattlers[1].header.flags |= ACTOR_FLAG_HIDDEN;
    g_BattlePartyBattlers[2].header.flags |= ACTOR_FLAG_HIDDEN;
}
