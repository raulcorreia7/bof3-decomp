#include "area134_13.h"

MATCH void func_801F44C0(void) {
    if (--g_Task->timer == 0) {
        Actor_Clear();
    } else {
        /* FAKE: gravity is s32 but asm accesses offset 0x20 as u16; active_flags is u8 but asm accesses 0x24 as s32 */
        FIELD(u16, g_Task, 0x20) -= 0x200;
        FIELD(s32, g_Task, 0x24) -= 0x100000;
        func_801F4B6C();
    }
}
