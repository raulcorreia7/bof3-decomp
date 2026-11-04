#include "area040_13.h"

MATCH void func_801F2C04(void) {
    s16 slot;

    slot = SP_REF(s16, 0x0u) = Actor_FindFree();
    if (slot != 0xFF) {
        func_801A4D54(D_801F4970);
    } else {
        g_ScriptState->cursor -= 2;
    }
}
