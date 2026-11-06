#include "area108_14.h"

MATCH s32 func_801F3A6C(void) {
    g_Task->unk_09 -= 1;
    if (g_Task->unk_09 != 0) {
        g_Task->tint.bytes.unk_5D -= 6;
        g_Task->tint.bytes.unk_5E -= 6;
        g_Task->tint.bytes.unk_5F -= 6;
    } else {
        g_Task->header.mode = 6;
    }
    func_801F3BA0();
    func_801F3C84();
}
