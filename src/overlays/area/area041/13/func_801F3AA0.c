#include "area041_13.h"

MATCH void func_801F3AA0(void) {
    s8 value;

    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 0) {
        Scene_SetupParty(3U);
        value = 0x1E;
    } else {
        Scene_SetupParty(4U);
        g_ScriptWorkRecord->header.flags = 0;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the value store in retail's schedule. */
        value = 0x28;
    }
    g_ScriptVars[1] = value;
}
