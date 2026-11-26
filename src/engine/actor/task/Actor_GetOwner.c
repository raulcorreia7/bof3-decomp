#include "engine/slus/slus.h"

/* classifies the active scratchpad work area.
 */
MATCH s32 Actor_GetOwner(void) {
    void* work;

    work = SELF(void);
    if (work == D_80143F48) {
        return 2;
    }
    if ((work == g_Game.members) || (work == &g_Game.members[1]) || (work == &g_Game.members[2])) {
        return 1;
    }
    return (work < g_PartyActors) ? 0 : 3;
}
