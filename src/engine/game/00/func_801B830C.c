#include "game_00.h"

MATCH void func_801B830C(void) {
    u8* work;
    u8  step;

    work = TASK_BYTES;
    if (work[9] == 0) {
        step     = work[10] + 1;
        work[10] = step;
        if (step == 3) {
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
        }
        func_801C24D0();
    }
    work    = TASK_BYTES;
    work[9] = work[9] - 1;
    func_801B0DFC();
    func_8014D978();
}
