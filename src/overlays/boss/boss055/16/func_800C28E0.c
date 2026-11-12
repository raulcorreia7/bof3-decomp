#include "boss055_16.h"

MATCH void func_800C28E0(void) {
    Area_SelectSceneRecord(0x30C);
    ((Actor*)g_Task)->unk_48       = 0;
    ((Actor*)g_Task)->active_flags = 0;
    ((Actor*)g_Task)->pos.z.fixed  = 0;
    func_800C2948();
    g_Task->header.step++;
}
