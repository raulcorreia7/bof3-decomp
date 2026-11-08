#include "area134_13.h"

MATCH void func_801F4214(void) {
    s32 count;

    if (D_801F5818 == 0) {
        Area_ClearWorkColumn();
    }
    g_Task->timer  = 0x80;
    count          = D_801F5818 + 1;
    D_801F5818     = count;
    g_Task->unk_06 = count;
    g_Task->header.mode += 1;
}
