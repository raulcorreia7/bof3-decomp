#include "area191_13.h"

MATCH void func_801F3BE0(void) {
    /* FAKE: Retail keeps the scene-flag address in v0; no pure-C shape moves
     * it off a0 without the pin (best draft 96.93%, work/.../801F3BE0). */
    FAKE_REG(u8*, flag, "v0");
    u8 counter;

    flag = g_SceneEventFlags;
    if (SYS_TestFlag(flag, 119)) {
        /* FAKE: Retail keeps the scene flag byte in a0 through the delay slot. */
        FAKE_REG(u8, flag_value, "a0");

        counter    = D_80144F56;
        flag       = &g_SceneState.flags_01;
        D_80144F54 = 0;
        D_80146880 = 0;
        D_80146881 = 0;
        flag_value = *flag;
        counter    = counter + 1;
        flag_value |= 1;
        D_80144F56 = counter;
        *flag      = flag_value;
        Actor_Clear();
    }
}
