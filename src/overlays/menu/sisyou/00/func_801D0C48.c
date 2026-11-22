#include "sisyou_00.h"

MATCH void func_801D0C48(void) {
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    g_MenuMasterScrollOffset = 4;
    g_MenuMasterSubStep++;
}
