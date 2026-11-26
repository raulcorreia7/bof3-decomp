#include "area108_14.h"

MATCH void func_801F3A14(void) {
    if (g_ScriptVars[0] == 0x2B) {
        SELF(Actor)->timer       = 16;
        SELF(Actor)->header.mode = 5;
    }
    Area_DrawScreenTint();
    func_801F3C84();
}
