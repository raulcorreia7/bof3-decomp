#include "game_00.h"

MATCH void func_801B00F8(void) {
    u8 countdown;

    func_801C3154();
    countdown = D_80146256;
    if (countdown != 0) {
        D_80146256 = countdown - 1;
    }
    func_801BDBC4();
    D_801CD0AC[FIELD(u8, g_Task, 1)]();
}
