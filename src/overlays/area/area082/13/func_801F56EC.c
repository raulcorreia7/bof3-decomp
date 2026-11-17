#include "area082_13.h"

MATCH void func_801F56EC(void) {
    Message_StartAreaMessage(SYS_TestFlag(g_SceneFlags, 4) ? MSG_008 : MSG_003);
    g_GameStateIndex = 2;
}
