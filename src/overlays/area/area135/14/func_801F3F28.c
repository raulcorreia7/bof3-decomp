#include "area135_14.h"

MATCH void func_801F3F28(void) {
    g_MessageRequest            = AREA135_MSG_PLATFORM_ACTIVATED;
    g_SceneEventState.selection = g_MessageChoice + 1;
    sprintf(g_TextVariables, D_801F2C04, g_SceneEventState.selection & BYTE_MASK);
    D_80147C97 = g_MessageChoice + 4;
}
