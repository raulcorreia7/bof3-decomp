#include "area173_14.h"

MATCH void func_801F4E90(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x58) != 0) {
        g_SceneEventMode = 0x26;
        g_SceneEventStep = 0xA;
    }
}
