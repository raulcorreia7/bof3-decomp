#include "engine/slus/slus.h"

/* clears bit 6 of the three boot flag bytes. */
MATCH void Party_ShowBattlers(void) {
    g_Game.members[0].header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Game.members[1].header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Game.members[2].header.flags &= ~ACTOR_FLAG_HIDDEN;
}
