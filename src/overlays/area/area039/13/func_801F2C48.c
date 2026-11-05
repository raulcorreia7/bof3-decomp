#include "area039_13.h"
#include "work/area_spad.h"

MATCH void func_801F2C48(void) {
    g_SpadWork->unk_0A   = 0x40;
    ((u8*)g_SpadWork)[4] = 1;
    *(u16*)((u8*)g_CurrentActor + 0x7E) -= 2;
}
