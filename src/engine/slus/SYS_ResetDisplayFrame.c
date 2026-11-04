#include "engine/slus/slus.h"

/* clears one ordering table and resets its four boot render flags.
 */
MATCH void SYS_ResetDisplayFrame(u8* work) {
    ClearOTagR((u_long*)(work + 0x70), 8);
    work[0x2C] = 1;
    work[0x2D] = 0;
    work[0x2E] = 0;
    work[0x2F] = 0;
}
