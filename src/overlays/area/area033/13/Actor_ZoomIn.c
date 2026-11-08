#include "area033_13.h"

/* func_801F3158 */
MATCH void Actor_ZoomIn(void) {
    u8* work;
    u8* work2;
    u8  timer;

    Actor_CenterOnScreen();

    work    = (u8*)g_Task;
    timer   = work[9];
    work[9] = timer - 1;
    work2   = (u8*)g_Task;
    *(s32*)(work + 0x40) += 0x2000;

    if (work2[9] == 0) {
        work2[0x48] = 0;
        work        = (u8*)g_Task;
        work[1]     = 3;
    }

    Area_AddActor();
}
