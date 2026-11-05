#include "area008_13.h"

MATCH void func_801F3AE8(void) {
    func_801F3C2C();
    func_801F3D18();

    ((Actor*)g_Task)->tint.signed_bytes.unk_5D = (((Actor*)g_Task)->tint.signed_bytes.unk_5D - 1);
    if (((Actor*)g_Task)->tint.signed_bytes.unk_5D < 0) {
        ((Actor*)g_Task)->tint.signed_bytes.unk_5D = 0x1D;
        ((Actor*)g_Task)->tint.signed_bytes.unk_5E = (((Actor*)g_Task)->tint.signed_bytes.unk_5E - 1);
    }
    if (((Actor*)g_Task)->tint.signed_bytes.unk_5E < 0) {
        ((Actor*)g_Task)->tint.signed_bytes.unk_5D = 0;
        ((Actor*)g_Task)->tint.signed_bytes.unk_5E = 0;
        g_Task->mode                               = (g_Task->mode + 1);
    }
}
