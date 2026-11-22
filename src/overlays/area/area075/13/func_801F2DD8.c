#include "area075_13.h"

MATCH void func_801F2DD8(void) {
    u8 tint;

    tint                          = TASK(Actor)->tint.bytes.rgb.r - 2;
    TASK(Actor)->tint.bytes.rgb.r = tint;
    /* FAKE: the shift preserves the retail zero test. */
    if ((tint << 24) == 0) {
        Actor_Clear();
    }
    if (!(TASK(Actor)->tint.bytes.rgb.r & 0x1F)) {
        TASK(Actor)->unk_06 += 1;
    }
    func_801F2E64(TASK(Actor)->unk_06, 1);
}
