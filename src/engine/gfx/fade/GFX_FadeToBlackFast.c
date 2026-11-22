#include "engine/slus/slus.h"

/* calls GFX_FadeRunBlack with delta 0x2000, semi-transparency 1 and order 0.
 */
/* func_8014EE40 */
MATCH void GFX_FadeToBlackFast(void) {
    GFX_FadeRunBlack(0x2000, 1, 0);
}
