#include "area082_13.h"

MATCH void func_801F56EC(void) {
    Message_StartAreaMessage(SYS_TestFlag(g_SceneFlags, 4) ? AREA082_MSG_NEED_SPECIAL_PERMISSION : AREA082_MSG_NEED_PATRIARCH_PERMISSION);
    D_80143BB0 = 2;
}
