#include "boss055_16.h"

MATCH void func_800C28E0(void) {
    Area_FindSceneRecord(0x30C);
    ((Actor*)g_SpadWork)->unk_48   = 0;
    ((Actor*)g_SpadWork)->flags_24 = 0;
    ((Actor*)g_SpadWork)->z.fixed  = 0;
    func_800C2948();
    SPAD_WORK_BYTES[2]++;
}
