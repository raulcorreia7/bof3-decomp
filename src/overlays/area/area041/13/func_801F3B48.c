#include "area041_13.h"

MATCH void func_801F3B48(void) {
    s32 choice;

    choice = g_MessageChoice;
    g_MessageRequest = D_801F5678[choice];
    if (choice == 0) {
        if (SYS_TestFlag(g_SceneFlags, 6) == 0) {
            SND_PlayCue(0x106);
            Item_Add(0, 0x28, 1, 0);
            SYS_SetFlag(g_SceneFlags, 6);
        }
    }
}
