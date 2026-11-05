#include "area103_13.h"

MATCH void func_801F57FC(void) {
    s32 value = Area_SampleHeight(FIELD(s32, g_Task, 0x34), FIELD(s32, g_Task, 0x38));

    FIELD(s16, g_Task, 0x3Eu) = value;
}
