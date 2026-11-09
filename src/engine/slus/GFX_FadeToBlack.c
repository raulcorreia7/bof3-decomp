#include "engine/slus/slus.h"

/* arms the full-screen tint fade with delta 0x800, semi-transparency 1 and order
 * 0 through GFX_RunBlackFade.
 */
/* func_8014EDF0 */
MATCH void GFX_FadeToBlack(void) {
    GFX_RunBlackFade(0x800, 1, 0);
}
