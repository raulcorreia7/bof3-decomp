#include "area174_13.h"

MATCH void func_801F4A5C(u8* pairs, s32 facing) {
    u8 offset;

    offset            = facing * 2;
    g_Task->direction = facing;
    Script_Select(pairs[offset]);
    g_Task->mirror = pairs[offset + 1];
}
