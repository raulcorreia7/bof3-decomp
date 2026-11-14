#include "engine/slus/slus.h"

MATCH void Area_AddActor(void) {
    u8     byte;
    u32    index;
    Actor* work;

    byte  = D_8014832C;
    index = byte;
    if (index < 30) {
        work              = g_Task;
        D_8014832C        = byte + 1;
        D_80148214[index] = work;
        if (work->header.flags & ACTOR_FLAG_SELECTION_EFFECT) {
            func_80161454(index);
        }
    }
}
