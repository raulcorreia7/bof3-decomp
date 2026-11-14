#include "area008_13.h"

MATCH void func_801F3AE8(void) {
    func_801F3C2C();
    func_801F3D18();

    (g_Task)->tint.signed_bytes.delta.red = ((g_Task)->tint.signed_bytes.delta.red - 1);
    if ((g_Task)->tint.signed_bytes.delta.red < 0) {
        (g_Task)->tint.signed_bytes.delta.red   = 0x1D;
        (g_Task)->tint.signed_bytes.delta.green = ((g_Task)->tint.signed_bytes.delta.green - 1);
    }
    if ((g_Task)->tint.signed_bytes.delta.green < 0) {
        (g_Task)->tint.signed_bytes.delta.red   = 0;
        (g_Task)->tint.signed_bytes.delta.green = 0;
        g_Task->header.mode                     = (g_Task->header.mode + 1);
    }
}
