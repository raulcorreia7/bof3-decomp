#include "area141_13.h"

/* Hand draft matches in schedule and shape with the g_ScriptState survivor local; the residual is one register
 * swap at the x.fixed load (retail keeps the load result in v0 and the 0xFFBB0000 constant in v1; every tried
 * form swaps them). Permuter candidate. */
INCLUDE_ASM(func_801F35E4);
