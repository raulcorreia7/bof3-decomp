#include "commu00_00.h"

MATCH void func_801F1770(void) {
    s8* state;

    EMI_LoadArchive(EMI_SLOT_COMMU01);
    state = &g_SceneEventStep;
    *state += 1;
}
