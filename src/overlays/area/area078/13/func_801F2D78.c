#include "area078_13.h"

MATCH void func_801F2D78(void) {
    s8 choice;

    choice           = g_MessageChoice;
    g_MessageRequest = D_801F4184[choice];
    switch (choice) {
        case 0:
            Game_SetScriptActive();
            g_ScriptVars[0] = 0;
            D_80146865      = 0;
            D_80146866      = 0;
            D_80146867      = 0;
            D_80146875      = 0;
            D_80146876      = 0;
            D_80146874      = 14;
            break;
        case 1:
            g_ScriptVars[0] = 0;
            break;
    }
}
