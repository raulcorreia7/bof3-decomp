#include "engine/slus/slus.h"

/* clears the halfword at 0x8014681C and the byte at 0x8014682E.
 */
MATCH void SND_XaStateIdle(void) {
    D_8014681C = 0;
    D_8014682E = 0;
}
