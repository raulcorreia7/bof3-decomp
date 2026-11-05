#include "battle_15.h"

MATCH void func_800ACF80(void) {
    u8 i;

    for (i = 0; i < 8; i++) {
        D_801EB630[i].flags  = 0;
        D_801EB630[i].mode   = 0;
        D_801EB630[i].step   = 0;
        D_801EB630[i].unk_03 = 0;
        D_801EB630[i].unk_04 = 0;
    }
}
