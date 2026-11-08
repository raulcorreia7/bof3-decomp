#include "boss033_16.h"
#include "area/spad.h"

MATCH void func_800C1ED8(void) {
    Actor* work;

    work          = (Actor*)g_Task;
    work->gravity = work->pos.z.fixed + 0x4000000;
    Actor_SelectScript(2);
    g_Task->param.unk_0B = 0x10;
    g_Task->header.step++;
}
