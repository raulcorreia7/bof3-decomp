#include "area099_13.h"

MATCH void func_801F30D0(void) {
    u8* flags;

    if (D_80143F03 == 1) {
        flags = D_80144EA0;
        if (SYS_TestFlag(flags, 28) && !SYS_TestFlag(flags, 29)) {
            Area_SetCellCode(35, 79, 0x51);
        } else {
            Area_SetCellCode(35, 79, 0x50);
        }
    }
}
