#include "engine/slus/slus.h"

/* calls GFX_RunWhiteFade with delta -0x800, semi-transparency 1 and order 0.
 */
/* func_8014EF58 */
MATCH void GFX_FadeFromWhite(void) {
    GFX_RunWhiteFade(-0x800, 1, 0);
}
