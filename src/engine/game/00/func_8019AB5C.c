#include "game_00.h"

MATCH void func_8019AB5C(void) {
    Actor* work;
    u8     value;

    work  = g_Task;
    value = work->timer;
    if (value == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 28u);
        Actor_Clear();
        return;
    }
    work->timer = (value - 1);
}
