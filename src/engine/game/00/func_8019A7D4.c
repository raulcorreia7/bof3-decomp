#include "game_00.h"

MATCH void func_8019A7D4(void) {
    Actor* work;

    work                       = g_Task;
    work->tint.bytes.rgb.blue  = 0;
    work->tint.bytes.rgb.green = 0;
    work->tint.bytes.rgb.red   = 0;
    Actor_Clear();
}
