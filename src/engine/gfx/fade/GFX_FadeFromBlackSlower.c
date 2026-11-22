#include "engine/slus/slus.h"

/* calls GFX_FadeRunBlack with delta -0x200, semi-transparency 1 and order 0.
 */
/* func_8014F1D4 */
MATCH void GFX_FadeFromBlackSlower(void) {
    GFX_FadeRunBlack(-0x200, 1, 0);
}
