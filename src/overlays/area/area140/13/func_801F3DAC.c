#include "area140_13.h"

MATCH void func_801F3DAC(void) {
    /* FAKE: retail keeps the actor row pointer in v0; pure C best 5 differing. */
    MATCH_REG(Actor*, work, "v0");
    u8  flag;
    u16 word;
    u32 near_five;

    work = g_CurrentActor;
    work->flags_74 &= 0xFE;
    flag = D_80145F09[0][0];
    if (((near_five = (u32)(flag - 5) < 2U), (word = flag), near_five) || ((word & 0xFF) == 7)) {
        SYS_SetFlag(g_SceneEventFlags, 0x54U);
        Area_SetCellPalette(2, 7);
        g_SpadWork->flags_00 = 0;
    }
}
