#include "sisyou_00.h"

MATCH void func_801D282C(void) {
    u8* state = &g_GameStateIndex;

    MasterMenuRequestMasterMessage(state, MASTER_MESSAGE_OFFER_REPLY);
}
