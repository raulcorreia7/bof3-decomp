#include "area092_13.h"

MATCH void func_801F2CD8(void) {
    s8 choice;

    choice           = g_MessageChoice;
    g_MessageRequest = D_801F41BC[choice];
    if (choice == 0) {
        Game_SetScriptActive();
        g_ScriptVars[0] = 0;
        D_80146865      = 0;
        D_80146866      = 0;
        D_80146867      = 0;
        D_80146875      = 0;
        D_80146874      = 8;
    }
}
