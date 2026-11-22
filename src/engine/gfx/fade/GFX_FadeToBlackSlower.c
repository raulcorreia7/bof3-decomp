#include "engine/slus/slus.h"

/* calls GFX_FadeRunBlack with delta 0x200, semi-transparency 1 and order 0.
 */
/* func_8014F1AC */
MATCH void GFX_FadeToBlackSlower(void) {
    GFX_FadeRunBlack(0x200, 1, 0);
}
