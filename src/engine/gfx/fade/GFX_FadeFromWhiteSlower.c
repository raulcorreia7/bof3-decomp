#include "engine/slus/slus.h"

/* calls GFX_FadeRunWhite with delta -0x200, semi-transparency 1 and order 0.
 */
/* func_8014F224 */
MATCH void GFX_FadeFromWhiteSlower(void) {
    GFX_FadeRunWhite(-0x200, 1, 0);
}
