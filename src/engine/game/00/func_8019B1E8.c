#include "game_00.h"

MATCH void func_8019B1E8(void) {
    Actor* work;
    s32    count;
    u8     flag;

    if (Script_AnimStepOnce() & BYTE_MASK) {
        ACTOR_COUNT_DOWN(SELF(Actor), count, timer);
        if ((count & BYTE_MASK) == 0) {
            SELF(Actor)->header.mode = 2;
        }
    }
    work = SELF(Actor);
    flag = work->option_flags;
    if ((flag != 0) && (flag == FIELD(u8, work, 0x58u))) {
        work->header.mode = 2;
    }
    Area_AddGridActor();
}
