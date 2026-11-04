#include "area015_13.h"

MATCH void func_801F2E60(void) {
    if (((Actor*)g_SpadWork)->unk_0A-- == 0) {
        ((Actor*)g_SpadWork)->unk_04 = 0;
    }
    if (D_80146876 == 0) {
        ((Actor*)g_SpadWork)->unk_04 = 0;
        ((Actor*)g_SpadWork)->unk_0A = 0;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
