#include "area192_13.h"

/* Best 5 differing: the world04/area168/13 func_801F49D4 form (constant local,
 * `state == one`) plus g_MessageRequest = 0xFFFF first. Rows 0x801F2D7C-84: the
 * state load and the 0xFFFF materialization swap (state-first reorders the lb
 * after the store, aliasing); rows 0x801F2D94/0x801F2DA0: the constant pseudo
 * a0 against v0. Same trap as func_801F49D4. */
INCLUDE_ASM(func_801F2D7C);
