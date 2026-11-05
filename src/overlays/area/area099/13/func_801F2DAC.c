#include "area099_13.h"

MATCH void func_801F2DAC(void) {
    FIELD(u8, g_Task, 0x0Au) = 0x48;
    FIELD(u8, g_Task, 0x04u) = 1;
    g_CurrentActor->unk_7E -= 2;
}
