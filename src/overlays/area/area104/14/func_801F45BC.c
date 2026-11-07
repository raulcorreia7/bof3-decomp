#include "area104_14.h"

MATCH void func_801F45BC(void) {
    u8* work = (u8*)g_Task;

    ((Callback*)D_801F6B10)[FIELD(u8, work, 0x2u)]();
    Area_StepRunGauge();
}
