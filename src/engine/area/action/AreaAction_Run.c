#include "engine/game/00/game_00.h"

/* The selected entry receives the caller's index (the same word the fallback
 * table at g_AreaActions is indexed by) and the work record's handler index. */
/* func_801ACE10 */
MATCH void AreaAction_Run(s32 step_index) {
    volatile Actor*    work;
    s32                index;
    AreaActionCallback handler;

    work  = GAME_WORK_AREA_PTR;
    index = work->unk_94 & 0x7F;
    if (index != 127) {
        handler = ((AreaActionCallback*)((AreaLoad*)g_AreaLoads[g_GameAreaId])->unk_3C)[index];
    } else {
        handler = g_AreaActions[(s16)step_index];
    }
    handler(step_index, index);
}
