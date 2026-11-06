#include "engine/slus/slus.h"

/* clears bit 6 of the three boot flag bytes.
 */
MATCH void Party_ShowBattlers(void) {
    g_BattlePartyBattlers[0].header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_BattlePartyBattlers[1].header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_BattlePartyBattlers[2].header.flags &= ~ACTOR_FLAG_HIDDEN;
}
