#include "area145_14.h"

/* func_801F4304 */
MATCH void Area_SkipIfHasKey(void) {
    if ((Item_VitalHas(VITAL_ITEM_KEY) & BYTE_MASK) != 0) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 3);
    }
}
