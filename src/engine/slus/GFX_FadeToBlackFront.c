#include "engine/slus/slus.h"

/* calls GFX_RunBlackFade with delta 0x800, semi-transparency 1 and order 2.
 */
/* func_8014EEE0 */
MATCH void GFX_FadeToBlackFront(void) {
    GFX_RunBlackFade(0x800, 1, 2);
}
