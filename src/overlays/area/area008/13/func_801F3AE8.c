#include "area008_13.h"

MATCH void func_801F3AE8(void) {
    func_801F3C2C();
    func_801F3D18();

    (g_Task)->tint.signed_bytes.unk_5D = ((g_Task)->tint.signed_bytes.unk_5D - 1);
    if ((g_Task)->tint.signed_bytes.unk_5D < 0) {
        (g_Task)->tint.signed_bytes.unk_5D = 0x1D;
        (g_Task)->tint.signed_bytes.unk_5E = ((g_Task)->tint.signed_bytes.unk_5E - 1);
    }
    if ((g_Task)->tint.signed_bytes.unk_5E < 0) {
        (g_Task)->tint.signed_bytes.unk_5D = 0;
        (g_Task)->tint.signed_bytes.unk_5E = 0;
        g_Task->header.mode                = (g_Task->header.mode + 1);
    }
}
