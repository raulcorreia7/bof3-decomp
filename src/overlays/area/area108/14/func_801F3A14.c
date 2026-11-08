#include "area108_14.h"

MATCH void func_801F3A14(void) {
    if (g_ScriptVars[0] == 0x2B) {
        g_Task->timer       = 0x10;
        g_Task->header.mode = 5;
    }
    Screen_DrawTint();
    func_801F3C84();
}
