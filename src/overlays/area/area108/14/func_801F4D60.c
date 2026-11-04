#include "area108_14.h"

MATCH void func_801F4D60(void) {
    g_SpadWork->unk_0B = Actor_FindFreeSlot();
    if (g_SpadWork->unk_0B == 0xFF) {
        g_ScriptState->cursor -= 2;
    }
}
