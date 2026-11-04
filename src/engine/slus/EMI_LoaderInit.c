#include "engine/slus/slus.h"

/* initializes the EMI/CD bootstrap state before the first active
 * entry is installed.
 */
/* func_80161F58 */
MATCH void EMI_LoaderInit(void) {
    s32           i;
    u8*           slot_state;
    u32           bootstrap_address;
    u8            empty_state;
    volatile u32* loader_state;

    while (CdInit() == 0) {
    }

    VSync(3);

    bootstrap_address = AREA_WORK;
    empty_state       = 0xFF;
    i                 = 0x17;
    loader_state      = &g_EmiRingBase;
    /* FAKE: +0x53 derivation keeps original address formation. */
    slot_state        = (u8*)loader_state + 0x53;

    *loader_state    = bootstrap_address;
    g_EmiServiceMode = 0;
    D_8014648A       = 0;
    D_8014648C       = 0;
    D_8014681A       = 0xFFFF;

    do {
        *slot_state = empty_state;
        i -= 1;
        slot_state -= 1;
    } while (i >= 0);
}
