#include "game_00.h"

MATCH void func_8019A7D4(void) {
    Actor* work;

    work                    = g_Task;
    work->tint.bytes.unk_5F = 0;
    work->tint.bytes.unk_5E = 0;
    work->tint.bytes.unk_5D = 0;
    Actor_Clear();
}
