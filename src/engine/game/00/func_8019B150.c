#include "game_00.h"

MATCH void func_8019B150(void) {
    Actor* work;
    s32    flag;

    flag = 1;
    Area_SceneSelectRecord(SELF(Actor)->unk_2C);

    SELF(Actor)->unk_48 = flag;

    SELF(Actor)->active_flags = 0;

    work         = SELF(Actor);
    work->mirror = (work->unk_06 >> 7);

    Script_Select((SELF(Actor)->unk_06 & 0x7F));
    SELF(Actor)->header.mode = flag;
}
