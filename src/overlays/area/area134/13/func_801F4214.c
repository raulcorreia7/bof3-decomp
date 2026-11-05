#include "area134_13.h"

MATCH void func_801F4214(void) {
    s32 temp_v0;

    if (D_801F5818 == 0) {
        Area_ClearWorkColumn();
    }
    g_SpadWork->unk_09 = 0x80;
    temp_v0            = D_801F5818 + 1;
    D_801F5818         = temp_v0;
    g_SpadWork->unk_06 = (u8)temp_v0;
    g_SpadWork->unk_01 += 1;
}
