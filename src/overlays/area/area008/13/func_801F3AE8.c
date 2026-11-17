#include "area008_13.h"

MATCH void func_801F3AE8(void) {
    func_801F3C2C();
    func_801F3D18();

    (g_Task)->tint.signed_bytes.delta.r = ((g_Task)->tint.signed_bytes.delta.r - 1);
    if ((g_Task)->tint.signed_bytes.delta.r < 0) {
        (g_Task)->tint.signed_bytes.delta.r = 0x1D;
        (g_Task)->tint.signed_bytes.delta.g = ((g_Task)->tint.signed_bytes.delta.g - 1);
    }
    if ((g_Task)->tint.signed_bytes.delta.g < 0) {
        (g_Task)->tint.signed_bytes.delta.r = 0;
        (g_Task)->tint.signed_bytes.delta.g = 0;
        g_Task->header.mode                 = (g_Task->header.mode + 1);
    }
}
