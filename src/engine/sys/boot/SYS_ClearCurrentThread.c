#include "engine/slus/slus.h"

/* clears the eight halfwords ending at offset 0x6E and the 16-byte run at
 * offset 0x70 of the g_SysCurrentThread work area.
 */
/* func_8014BA04 */
MATCH void SYS_ClearCurrentThread(void) {
    s32 i;

    for (i = 7; i >= 0; i--) {
        g_SysCurrentThread->tail.clear.halfword[i] = 0;
    }
    for (i = 0; i < 16; i++) {
        g_SysCurrentThread->tail.clear.byte[i] = 0;
    }
}
