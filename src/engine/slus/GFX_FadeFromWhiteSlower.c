#include "engine/slus/slus.h"

/* calls GFX_RunWhiteFade with delta -0x200, semi-transparency 1 and order 0.
 */
/* func_8014F224 */
MATCH void GFX_FadeFromWhiteSlower(void) {
    GFX_RunWhiteFade(-0x200, 1, 0);
}
