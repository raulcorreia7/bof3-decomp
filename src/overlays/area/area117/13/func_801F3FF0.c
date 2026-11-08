#include "area117_13.h"

MATCH void func_801F3FF0(void) {
    s32 choice;

    choice           = g_MessageChoice;
    g_MessageRequest = D_801F55D8[choice];
    if (choice < 0) {
        return;
    }
    if (choice < 5) {
        g_ScriptVars[0] = 0xA;
        SND_PlayCue(0x205);
    }
}
