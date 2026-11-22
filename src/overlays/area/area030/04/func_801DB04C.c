#include "area030_04.h"

/* Latches the rod row's +0x07 speed while the step timer counts down and its
 * cursor return speed otherwise. */
MATCH void func_801DB04C(void) {
    if (TASK(FishingState)->timer != 0) {
        D_801E31F8 = 2;
        D_8014421C = g_FishingRodRow->unk_07;
    } else {
        D_801E31F8 = 1;
        D_8014421C = g_FishingRodRow->cursor_return_speed;
    }
}
