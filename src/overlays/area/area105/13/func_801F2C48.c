#include "area105_13.h"

MATCH void func_801F2C48(void) {
    if (SCENARIO_PROGRESS == 0x20C) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
        FIELD(u8, g_Self, 0x2u)++;
    }
}
