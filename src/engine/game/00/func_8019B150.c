#include "game_00.h"

MATCH void func_8019B150(void) {
    Actor* work;
    s32    flag;

    flag = 1;
    Area_SceneSelectRecord(TASK(Actor)->unk_2C);

    TASK(Actor)->unk_48 = flag;

    TASK(Actor)->active_flags = 0;

    work         = TASK(Actor);
    work->mirror = (work->unk_06 >> 7);

    Script_Select((TASK(Actor)->unk_06 & 0x7F));
    TASK(Actor)->header.mode = flag;
}
