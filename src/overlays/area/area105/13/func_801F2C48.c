#include "area105_13.h"

MATCH void func_801F2C48(void) {
    if (SCENARIO_PROGRESS == 0x20C) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 2));
        FIELD(u8, g_Task, 0x2u)++;
    }
}
