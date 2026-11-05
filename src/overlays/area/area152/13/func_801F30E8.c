#include "area152_13.h"

MATCH void func_801F30E8(void) {
    u8* scratch;
    u8* check;

    Actor_CenterOnScreen();

    scratch = (u8*)g_SpadWork;
    scratch[0x09] -= 1;

    check = (u8*)g_SpadWork;
    *(s32*)(scratch + 0x40) += 0x2000;

    if (check[0x09] == 0) {
        check[0x48]             = 0;
        ((u8*)g_SpadWork)[0x01] = 3;
    }

    Area_AddActor();
}
