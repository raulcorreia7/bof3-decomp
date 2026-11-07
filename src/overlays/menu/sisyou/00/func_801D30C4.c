#include "sisyou_00.h"

MATCH void func_801D30C4(void) {
    u8* state = &g_GameStateIndex;

    MasterMenuRequestMasterMessage(state, MASTER_MESSAGE_ENROLLED_MORE_QUERY);
}
