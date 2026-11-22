#include "engine/slus/slus.h"

/* calls GFX_FadeRunBlack with delta 0x400, semi-transparency 1 and order 0.
 */
/* func_8014EE90 */
MATCH void GFX_FadeToBlackSlow(void) {
    GFX_FadeRunBlack(0x400, 1, 0);
}
