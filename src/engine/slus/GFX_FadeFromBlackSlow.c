#include "engine/slus/slus.h"

/* calls GFX_RunBlackFade with delta -0x400, semi-transparency 1 and order 0. */
/* func_8014EEB8 */
MATCH void GFX_FadeFromBlackSlow(void) {
    GFX_RunBlackFade(-0x400, 1, 0);
}
