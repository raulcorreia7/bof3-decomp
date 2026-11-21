#include "area135_14.h"

MATCH void func_801F3F28(void) {
    g_UiMessageRequest          = MSG_AREA135_PLATFORM_ACTIVATED;
    g_SceneEventState.selection = g_UiMessageChoice + 1;
    sprintf(g_TextVariables, D_801F2C04, g_SceneEventState.selection & BYTE_MASK);
    D_80147C97 = g_UiMessageChoice + 4;
}
