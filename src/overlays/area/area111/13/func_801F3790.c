#include "area111_13.h"

MATCH void func_801F3790(void) {
    u32 slot = -(((s32)g_CurrentActor - (s32)D_80147A58) * 0xD79435E5) >> 3;

    if (D_80146867 != (16 << slot)) {
        g_ScriptState->cursor -= 2;
    }
}
