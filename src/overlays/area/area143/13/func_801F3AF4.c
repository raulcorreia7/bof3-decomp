#include "area143_13.h"

/* first differing instruction: lui v1,%hi(g_ScriptWorkRecord) at +0x28 (retail) against the lhu 0x7E scheduled early (candidate); the else-if shape is exact but retail keeps lhu 0x7E after the two stores (0x98 bytes against 0x94). Local record pointer and view-cast of g_ScriptWorkRecord tried. */
INCLUDE_ASM(func_801F3AF4);
