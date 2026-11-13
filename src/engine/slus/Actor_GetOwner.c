#include "engine/slus/slus.h"

/* classifies the active scratchpad work area.
 */
MATCH s32 Actor_GetOwner(void) {
    u8* work;

    work = (u8*)g_Task;
    if (work == D_80143F48) {
        return 2;
    }
    if ((work == (u8*)g_Game.members) || (work == (u8*)&g_Game.members[1]) || (work == (u8*)&g_Game.members[2])) {
        return 1;
    }
    return (work < (u8*)D_80147A58) ? 0 : 3;
}
