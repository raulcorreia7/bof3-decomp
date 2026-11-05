#include "area108_14.h"

void func_801F3A6C(void) {
    g_SpadWork->unk_09 -= 1;
    if (g_SpadWork->unk_09 != 0) {
        g_SpadWork->tint.bytes.unk_5D -= 6;
        g_SpadWork->tint.bytes.unk_5E -= 6;
        g_SpadWork->tint.bytes.unk_5F -= 6;
    } else {
        g_SpadWork->unk_01 = 6;
    }
    func_801F3BA0();
    func_801F3C84();
}
