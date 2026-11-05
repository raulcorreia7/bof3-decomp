#include "boss055_16.h"

MATCH void func_800C2780(void) {
    Area_FindSceneRecord(0x30D);
    ((Actor*)g_SpadWork)->unk_48   = 0;
    ((Actor*)g_SpadWork)->flags_24 = 0;
    ((Actor*)g_SpadWork)->z.fixed  = 0;
    func_800C27E8();
    SPAD_WORK_BYTES[2]++;
}
