#include "commu00_00.h"

MATCH void func_801F1770(void) {
    s8* state;

    EMI_LoaderStreamInitSlot(EMI_SLOT_COMMU01);
    state = &g_SaveData.scene_event.step;
    *state += 1;
}
