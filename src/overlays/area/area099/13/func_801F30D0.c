#include "area099_13.h"

MATCH void func_801F30D0(void) {
    u8* flags;

    if (D_80143F03 == 1) {
        flags = D_80144EA0;
        if (SYS_TestFlag(flags, 0x1C) && !SYS_TestFlag(flags, 0x1D)) {
            Area_SetCellCode(0x23, 0x4F, 0x51);
        } else {
            Area_SetCellCode(0x23, 0x4F, 0x50);
        }
    }
}
