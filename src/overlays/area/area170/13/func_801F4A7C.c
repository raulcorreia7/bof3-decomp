#include "area170_13.h"

/* Set the shared game work word's 0x1000 and 0x10 flags. */
MATCH void func_801F4A7C(void) {
    g_GameFlags |= 0x1010; /* 0x1000 is set by func_801BFF9C; Game_RequestLeaderSwitch reads 0x10 */
}
