#include "boss055_16.h"

MATCH void func_800C2A40(void) {
    Area_FindSceneRecord(0x30C);
    ((Actor*)g_Task)->unk_48   = 0;
    ((Actor*)g_Task)->flags_24 = 0;
    ((Actor*)g_Task)->z.fixed  = 0;
    func_800C2AA8();
    TASK_BYTES[2]++;
}
