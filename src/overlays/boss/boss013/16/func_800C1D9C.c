#include "boss013_16.h"

MATCH void func_800C1D9C(void) {
    Area_SelectSceneRecord(0xF9);
    g_Task->unk_24 &= 0xFE;
    Script_Select(2);
    g_Task->header.step++;
}
