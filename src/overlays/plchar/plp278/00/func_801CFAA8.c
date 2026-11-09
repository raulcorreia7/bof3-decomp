#include "plp278_00.h"

MATCH void func_801CFAA8(void) {
    u8 direction;
    
    direction = g_Task->direction_08;
    if (!(direction & 1)) {
        g_Task->direction_08 = (direction - 1) & 7;
        if (!(func_8019601C() & 0xFF)) {
            g_Task->direction_08 = (g_Task->direction_08 + 2) & 7;
            if (!(func_8019601C() & 0xFF)) {
                g_Task->direction_08 = (g_Task->direction_08 - 2) & 7;
            }
        }
    }
    func_8019601C();
    g_Task->param.unk_0B = 0;
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
}
