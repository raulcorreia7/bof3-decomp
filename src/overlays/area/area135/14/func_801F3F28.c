#include "area135_14.h"

MATCH void func_801F3F28(void) {
    g_MessageRequest      = 0x84;
    g_SceneEventSelection = g_MessageChoice + 1;
    sprintf(g_TextVariables, D_801F2C04, g_SceneEventSelection & 0xFF);
    D_80147C97 = g_MessageChoice + 4;
}
