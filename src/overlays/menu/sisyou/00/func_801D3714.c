#include "sisyou_00.h"

MATCH void func_801D3714(void) {
    u8* state = &g_GameStateIndex;

    MasterMenuRequestMasterMessage(state, MASTER_MESSAGE_DISMISSED_MORE_QUERY);
}
