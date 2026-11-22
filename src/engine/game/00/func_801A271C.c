#include "game_00.h"

MATCH void func_801A271C(void* record) {
    u8 timer;

    timer = FIELD(u8, record, 0x75u);
    if (timer == 0) {
        g_Task->header.mode = g_Task->unk_03;
        return;
    }
    FIELD(u8, record, 0x75u) = timer - 1;
    FIELD(u8, record, 0x74u) |= 0x10;
}
