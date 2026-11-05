#include "area041_13.h"

MATCH void func_801F32FC(void) {
    g_SpadWork->unk_09 += 1;
    g_SpadWork->x.fixed = ((g_SpadWork->unk_09 & 1) * 8) - 0x2B80;
    if ((u8)g_SpadWork->unk_09 >= 8U) {
        g_SpadWork->unk_09  = 0;
        g_SpadWork->x.fixed = -0x2B80;
        g_SpadWork->state_02 += 1;
    }
    func_801F2EFC();
    func_801F3064();
}
