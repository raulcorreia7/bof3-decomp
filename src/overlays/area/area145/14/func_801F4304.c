#include "area145_14.h"

MATCH void func_801F4304(void) {
    if ((Item_VitalHas(VITAL_ITEM_KEY) & 0xFF) != 0) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 3);
    }
}
