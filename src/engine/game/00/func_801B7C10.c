#include "game_00.h"

MATCH void func_801B7C10(void) {
    if (func_801C520C() & BYTE_MASK) {
        FIELD(u8, g_Task, 4u)++;
    }
}
