#include "area041_13.h"
#include "work/area_spad.h"

MATCH void func_801F3E80(void) {
    g_Task->vx = 0x4000;
    func_801F4118();
    g_Task->unk_0A = 7;
    g_Task->unk_04 = 1;
    g_Game.current->u.field.unk_122 -= 2;
}
