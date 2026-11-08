#include "boss036_16.h"
#include "area/spad.h"

MATCH void func_800C1F44(void) {
    g_Task->param.unk_0B = 0;
    g_Task->timer        = 0;
    Actor_SelectScript(1);
    func_8014D978();
    Area_AddActor();
    g_Task->header.step++;
}
