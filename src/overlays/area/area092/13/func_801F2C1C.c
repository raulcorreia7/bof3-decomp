#include "area092_13.h"

MATCH void func_801F2C1C(void) {
    s8 choice = g_MessageChoice;

    g_MessageRequest = D_801F41B0[choice];
    switch (choice) {
        case 2:
            Game_SetScriptActive();
            D_80146875 = 10;
            break;
        case 3:
            Game_SetScriptActive();
            D_80146875 = 30;
            break;
        case 4:
            Game_SetScriptActive();
            D_80146875 = 20;
            break;
        case 0:
        case 1:
        case 5:
        default:
            return;
    }
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146874      = 8;
}
