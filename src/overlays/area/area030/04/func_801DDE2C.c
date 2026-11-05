#include "area030_04.h"

/* Points the two character record cursors at the selected table rows
 * (20-byte and 10-byte strides) when their selector bytes are set. */
MATCH void func_801DDE2C(void) {
    if (D_80145026 != 0) {
        D_801E3210 = (FishingTarget*)(D_801E2720 + D_80145026 * sizeof(FishingTarget));
    }
    if (D_80145028 != 0) {
        D_801E320C = (FishingCharRow*)(D_801E2748 + D_80145028 * 10);
    }
}
