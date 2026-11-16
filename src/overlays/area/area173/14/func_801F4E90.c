#include "area173_14.h"

MATCH void func_801F4E90(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 88) != 0) {
        g_SceneEventState.mode = 0x26;
        g_SceneEventState.step = 0xA;
    }
}
