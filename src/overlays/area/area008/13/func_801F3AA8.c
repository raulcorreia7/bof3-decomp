#include "area008_13.h"

/* Thirty-second field countdown: func_801F3AA8 starts it, func_801F3AE8
 * advances it at 30 frames per second, and func_801F3C2C draws
 * seconds/hundredths. The work row's tint bytes hold it (0x5D and 0x5E). */
MATCH void func_801F3AA8(void) {
    (g_Task)->tint.signed_bytes.unk_5D = 0;
    (g_Task)->tint.signed_bytes.unk_5E = 30;
    (g_Task)->header.mode              = (g_Task)->header.mode + 1;
}
