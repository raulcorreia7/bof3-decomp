#include "engine/slus/slus.h"

/* clears g_MessageState when D_80148333 is 2.
 */
MATCH void func_80151820(void) {
    if (D_80148333[0] == 2) {
        g_MessageState.state_00 = 0;
    }
}
