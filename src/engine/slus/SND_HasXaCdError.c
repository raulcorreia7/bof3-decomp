#include "engine/slus/slus.h"

/* tests bit 0x10 of the byte at 0x80146824.
 */

MATCH bool SND_HasXaCdError(void) {
    if ((D_80146824[0] & 0x10) == 0)
        return false;
    return true;
}
