#include "area140_13.h"

MATCH void func_801F476C(void) {
    u8* work;

    work = SELF(u8);
    SYS_ClearFlag(g_SceneEventFlags, work[0xB]);
    work = SELF(u8);
    Area_CellSetPalette(FIELD(s16, work, 0x36), FIELD(s16, work, 0x3A));
    Actor_Clear();
}
