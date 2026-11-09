#include "engine/slus/slus.h"

/* calls GFX_RunBlackFade with delta -0x800, semi-transparency 1 and order 0. */
/* func_8014EE18 */
MATCH void GFX_FadeFromBlack(void) {
    GFX_RunBlackFade(-0x800, 1, 0);
}
