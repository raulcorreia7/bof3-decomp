#include "engine/slus/slus.h"

/* calls GFX_FadeRunBlack with delta -0x800, semi-transparency 1 and order 2.
 */
/* func_8014EF08 */
MATCH void GFX_FadeFromBlackFront(void) {
    GFX_FadeRunBlack(-0x800, 1, 2);
}
