#include "game_00.h"

MATCH void func_8019A7D4(void) {
    Actor* work;

    work                   = g_Task;
    work->tint.bytes.rgb.b = 0;
    work->tint.bytes.rgb.g = 0;
    work->tint.bytes.rgb.r = 0;
    Actor_Clear();
}
