#include "game_00.h"

/* Per-slot column views over the 0x98-byte work records: the trailing padding
 * carries the record stride so each column keeps its own field base. */
/* Column bases: +0x2E, +0x30 and +0x29 of every work record. */

MATCH void func_8019B284(void) {
    Actor* work;
    u8     index;

    work  = g_Task;
    index = work->unk_0B;
    if ((work->header.flags & ACTOR_FLAG_HIDDEN) == 0) {
        D_801468B6[index].value = D_801468B6[index].value + work->unk_2E;
        D_801468B8[index].value = D_801468B8[index].value + work->unk_30;
        D_801468B1[index].value = work->unk_29;
    }
    if (!ACTOR_IN_USE(g_Actors[index])) {
        Actor_Clear();
    }
}
