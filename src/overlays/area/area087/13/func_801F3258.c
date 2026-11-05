#include "area087_13.h"

MATCH void func_801F3258(void) {
    Actor* scratch;
    Actor* scratch2;
    u8     timer;

    Actor_CenterOnScreen();

    scratch                    = g_SpadWork;
    timer                      = *(u8*)(((u8*)scratch + 9));
    *(u8*)(((u8*)scratch + 9)) = timer - 1;
    scratch2                   = g_SpadWork;
    scratch->unk_40 += 0x2000;

    if (((u8*)scratch2)[9] == 0) {
        scratch2->unk_48        = 0;
        ((u8*)g_SpadWork)[0x01] = 3;
    }

    Area_AddActor();
}
