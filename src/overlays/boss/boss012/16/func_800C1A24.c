#include "boss012_16.h"
#include "area/spad.h"

MATCH void func_800C1A24(void) {
    func_800C1C08(FIELD(u16, g_Task, 0x20));
    func_800C1CD8(FIELD(u16, g_Task, 0x20));
    g_Task->gravity += 2;
    if (g_Task->gravity == 0x56) {
        g_Task->unk_03 = 3;
    }
}
