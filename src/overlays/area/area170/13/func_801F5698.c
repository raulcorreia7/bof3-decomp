#include "area170_13.h"

MATCH s32 func_801F5698(void) {
    s8* flags;

    Game_SetScriptActive();
    flags      = &D_801448EB;
    *flags     = 0x25;
    D_801448EC = 0x28;
    SYS_ClearFlag(flags + 0x63D, 0x7EU);
    return 1;
}
