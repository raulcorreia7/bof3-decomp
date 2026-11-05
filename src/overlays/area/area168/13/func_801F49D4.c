#include "area168_13.h"

/* Best: structure exact, 7 differing rows all register renames (state retail v1
 * against a0, value retail v0 against v1). Tried nested and flat arms, a state
 * local in both declaration orders, s8/u16/s32 value, permuter 45 over two
 * windows. Next lever: a form whose first pseudo claims v0 before the state. */
INCLUDE_ASM(func_801F49D4);
