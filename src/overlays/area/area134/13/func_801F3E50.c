#include "area134_13.h"

MATCH void func_801F3E50(void) {
    if (g_PadStates[0].held == (PADLup | PADLright) || g_PadStates[0].held == (PADLright | PADLdown) || g_PadStates[0].held == PADLright) {
        SELF(Actor)->header.mode = 1;
    }
}
