#include "engine/slus/slus.h"

/* calls GFX_RunBlackFade with delta 0x100, semi-transparency 1 and order 0. */
/* func_8014F438 */
MATCH void GFX_FadeToBlackSlowest(void) {
    GFX_RunBlackFade(0x100, 1, 0);
}
