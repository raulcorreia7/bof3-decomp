#include "game_00.h"

MATCH void func_8019F75C(void) {
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);
    u8* dst;
    s32 index;
    s32 limit;

    dst   = MEM_PTR(u8, 0x800F0800u);
    limit = *g_Task->range_54.table * 0x28;
    index = 0;
    if (limit > 0) {
        do {
            *dst = *g_Task->script;
            g_Task->script += 1;
            index += 1;
            dst += 1;
        } while (index < limit);
    }
    g_Task->script = MEM_PTR(u8, 0x800F0800u);
    func_8019D648();
    func_8019D9C0();
    g_Task->timer = 0x10;
}
