#include "area134_13.h"

MATCH void func_801F4214(void) {
    s32 temp_v0;

    if (D_801F5818 == 0) {
        Area_ClearWorkColumn();
    }
    g_Task->unk_09 = 0x80;
    temp_v0        = D_801F5818 + 1;
    D_801F5818     = temp_v0;
    g_Task->unk_06 = temp_v0;
    g_Task->header.mode += 1;
}
