#include "area035_13.h"

MATCH void func_801F2D54(void) {
    FIELD(u8, g_CurrentActor, 0x74u) = (FIELD(u8, g_CurrentActor, 0x74u) & 0xFE);
    *SP_REF(s8*, 0x44)               = 0;
}
