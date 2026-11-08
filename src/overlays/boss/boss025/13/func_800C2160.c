#include "boss025_13.h"

MATCH void func_800C2160(void) {
    u8* flag = &g_Battle.boss_flags;
    *flag |= 0x20;
}
