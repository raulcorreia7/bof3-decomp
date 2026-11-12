#include "area092_13.h"

MATCH void func_801F2DD4(void) {
    s8 choice;
    u8 event;

    choice           = g_MessageChoice;
    g_MessageRequest = D_801F41C4[choice];
    switch (choice) {
        case 0:
            Game_SetScriptActive();
            event = 60;
            break;
        case 1:
            if (SYS_TestFlag(g_SceneFlags, 27) == 0) {
                Game_SetScriptActive();
                event = 18;
            } else {
                Game_SetScriptActive();
                event = 35;
            }
            break;
        default:
            return;
    }
    D_80146875      = event;
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146874      = 7;
}
