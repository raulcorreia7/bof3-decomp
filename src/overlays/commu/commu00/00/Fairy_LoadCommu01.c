#include "commu00_00.h"

MATCH void Fairy_LoadCommu01(void) {
    s8* state;

    EMI_ArchiveLoad(EMI_SLOT_COMMU01);
    state = &g_SceneEventState.step;
    *state += 1;
}
