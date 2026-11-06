#include "area134_13.h"

MATCH void func_801F3E50(void) {
    if (g_InputHeld == (PADLup | PADLright) || g_InputHeld == (PADLright | PADLdown) || g_InputHeld == PADLright) {
        g_Task->header.mode = 1;
    }
}
