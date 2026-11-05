#include "area172_13.h"

MATCH void func_801F434C(void) {
    u8 size;
    u8 i;

    size = g_PartySize;
    i    = 0;
    if (size != 0) {
        do {
            if (D_80145F09[i][0] == 4) {
                g_ScriptState->cursor += 3;
                return;
            }
            i += 1;
        } while (i < size);
    }
}
