#include "sisyou_00.h"

MATCH void func_801D2B64(void) {
    u8* state = &g_GameStateIndex;

    if (*state == 2) {
        return;
    }
    Message_StartAreaMessage((s16)(g_MasterMessageIds[D_801448ED] + 4));
    *state          = 2;
    g_MasterStep    = 6;
    g_MasterSubStep = 0;
}
