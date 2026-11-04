#include "engine/slus/slus.h"

/* publishes the PadRead(0) result into the two pad state records, keeping
 * the previous value and the newly pressed bits.
 */
MATCH void SYS_UpdateKeyState(void) {
    /* FAKE: pins three live values to the retail v0/v1/a1 homes. */
    MATCH_REG(u32, pad, "v0");
    MATCH_REG(u32, high, "v1");
    u16 old_first;
    MATCH_REG(u16, old_second, "a1");
    /* FAKE: the volatile first record keeps the retail access order. */
    volatile u16* first;
    u16*          second;

    pad   = PadRead(0);
    first = &D_80145AA6;
    /* FAKE: keeps the record base in one register. */
    MATCH_FAKE_OPAQUE(first);
    old_first = first[-1];
    first[-1] = (u16)pad;
    second    = &D_80145AAE;
    /* FAKE: keeps the record base in one register. */
    MATCH_FAKE_OPAQUE(second);
    old_second = second[-1];
    high       = pad >> 16;
    second[-1] = (u16)high;
    first[0]   = old_first;
    first[1]   = (u16)(pad & (pad ^ old_first));
    second[0]  = old_second;
    second[1]  = (u16)(high & (high ^ old_second));
}
