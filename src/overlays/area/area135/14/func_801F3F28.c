#include "area135_14.h"

MATCH void func_801F3F28(void) {
    g_UIMessageRequest          = MSG_AREA135_PLATFORM_ACTIVATED;
    g_SceneEventState.selection = g_UIMessageChoice + 1;
    sprintf(g_TextVariables, D_801F2C04, g_SceneEventState.selection & BYTE_MASK);
    g_PartyActors[3].unk_77 = g_UIMessageChoice + 4;
}
