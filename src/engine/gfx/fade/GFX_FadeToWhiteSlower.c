#include "engine/slus/slus.h"

/* calls GFX_FadeRunWhite with delta 0x200, semi-transparency 1 and order 0.
 */
/* func_8014F1FC */
MATCH void GFX_FadeToWhiteSlower(void) {
    GFX_FadeRunWhite(0x200, 1, 0);
}
