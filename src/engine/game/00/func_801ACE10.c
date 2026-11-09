#include "game_00.h"

/* The selected entry receives the caller's index (the same word the fallback table at D_801C890C is indexed by) and the work record's handler index. */
MATCH void func_801ACE10(s32 handler_index) {
    volatile Actor* work;
    s32             index;
    ActorWorkFunc   handler;

    work  = GAME_WORK_AREA_PTR;
    index = work->unk_94 & 0x7F;
    if (index != 127) {
        handler = FIELD(ActorWorkFunc*, g_AreaLoads[g_GameAreaId], 0x3Cu)[index];
    } else {
        handler = D_801C890C[(s16)handler_index];
    }
    handler(handler_index, index);
}
