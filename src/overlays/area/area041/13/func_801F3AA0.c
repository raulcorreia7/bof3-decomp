#include "area041_13.h"

MATCH void func_801F3AA0(void) {
    s8 value;

    g_MessageRequest = 0xFFFF;
    if (D_801490C7 == 0) {
        func_801BE1B0(3U);
        value = 0x1E;
    } else {
        func_801BE1B0(4U);
        g_ScriptWorkRecord->flags_00 = 0;
        do {
        } while (0); /* FAKE: the empty loop keeps the value store in retail's schedule. */
        value = 0x28;
    }
    D_80146865 = value;
}
