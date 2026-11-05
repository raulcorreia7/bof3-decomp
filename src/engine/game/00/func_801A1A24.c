#include "game_00.h"

MATCH void func_801A1A24(u8* record) {
    Actor* work = g_Task;

    if (work->unk_06 != 8) {
        record[0x74] |= ACTOR_FLAG_SCRIPT_REQUEST;
    }
}
