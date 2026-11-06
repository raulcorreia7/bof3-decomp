#include "area100_13.h"

MATCH s32 func_801F2CC0(void) {
    s32 value;

    FIELD(s32, g_Task, 0x34u) = TO_COORD(10);
    FIELD(s32, g_Task, 0x38u) = TO_COORD(99);
    value                     = Area_SampleHeight(FIELD(s32, g_Task, 0x34u), FIELD(s32, g_Task, 0x38u)) << 16;
    FIELD(s32, g_Task, 0x3Cu) = value;
    FIELD(u8, g_Task, 0x1u)++;
}
