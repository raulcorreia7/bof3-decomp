#include "game_00.h"

/* The selected entry receives the caller's index (the same word the fallback
 * table at g_FieldActions is indexed by) and the work record's handler index. */
/* func_801ACE10 */
MATCH void FieldAction_Run(s32 step_index) {
    volatile Actor*     work;
    s32                 index;
    FieldActionCallback handler;

    work  = GAME_WORK_AREA_PTR;
    index = work->unk_94 & 0x7F;
    if (index != 127) {
        handler = FIELD(FieldActionCallback*, g_AreaLoads[g_GameAreaId], 0x3Cu)[index];
    } else {
        handler = g_FieldActions[(s16)step_index];
    }
    handler(step_index, index);
}
