#include "area041_13.h"

MATCH void func_801F3AA0(void) {
    s8 value;

    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 0) {
        func_801BE1B0(3U);
        value = 0x1E;
    } else {
        func_801BE1B0(4U);
        g_ScriptWorkRecord->header.flags = 0;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the value store in retail's schedule. */
        value = 0x28;
    }
    D_80146865 = value;
}
