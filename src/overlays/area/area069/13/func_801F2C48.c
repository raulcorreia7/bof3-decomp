#include "area069_13.h"
#include "work/area_spad.h"

MATCH void func_801F2C48(void) {
    TASK_BYTES[0x0A] = 0x40;
    TASK_BYTES[0x04] = 1;
    g_Game.current->u.field.unk_122 -= 2;
}
