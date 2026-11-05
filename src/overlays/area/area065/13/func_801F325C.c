#include "area065_13.h"

MATCH void func_801F325C(void) {
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
        scratch2->unk_48   = 0;
        g_SpadWork->unk_01 = 3;
    }

    Area_AddActor();
}
