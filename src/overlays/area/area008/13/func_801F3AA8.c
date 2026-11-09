#include "area008_13.h"

/* Thirty-second field countdown. */
MATCH void func_801F3AA8(void) {
    (g_Task)->tint.signed_bytes.unk_5D = 0;
    (g_Task)->tint.signed_bytes.unk_5E = 30;
    (g_Task)->header.mode              = (g_Task)->header.mode + 1;
}
