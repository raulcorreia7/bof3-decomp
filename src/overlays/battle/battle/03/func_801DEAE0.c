#include "battle_03.h"

MATCH void func_801DEAE0(void) {
    u8  local_18[6];
    u32 x;
    u32 mode;

    __builtin_memcpy(local_18, s_BattleCueIds, sizeof(local_18));
    mode = D_801463D0;
    switch (mode) {
        case 1u:
            x = local_18[RANDOM_MASK(1u)];
            break;
        case 0u:
            x = local_18[4u + RANDOM_MASK(1u)];
            break;
        case 2u:
        case 3u:
        case 4u:
            x = local_18[2u + RANDOM_MASK(1u)];
            break;
        default:
            x = local_18[4u + RANDOM_MASK(1u)];
            break;
    }

    /* FAKE: keeps a1 staged before arg4. */
    FAKE_CLOBBER_A1();
    /* FAKE: keeps a2 staged before arg4. */
    FAKE_CLOBBER_A2();
    /* FAKE: keeps a3 staged before arg4. */
    FAKE_CLOBBER_A3();
    func_801DE60C(0u, 2u, 0u, 0u, 255u, Message_GetText(x));
}
