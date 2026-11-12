#include "boss055_16.h"

MATCH void func_800C2780(void) {
    Area_SelectSceneRecord(0x30D);
    ((Actor*)g_Task)->unk_48       = 0;
    ((Actor*)g_Task)->active_flags = 0;
    ((Actor*)g_Task)->pos.z.fixed  = 0;
    func_800C27E8();
    g_Task->header.step++;
}
