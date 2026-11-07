#include "sisyou_00.h"

MATCH void func_801D29C8(void) {
    u8* state = &g_GameStateIndex;

    MasterMenuRequestMasterMessage(state, MASTER_MESSAGE_ALL_ENROLLED_QUERY);
}
