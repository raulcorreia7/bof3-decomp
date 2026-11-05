#include "area135_14.h"

/* Hand draft matches in shape but the first global's address lands in a2 instead of v1
 * (lui at 0x801F603C); the tried forms (commuted multiplies, a scale survivor local) do not move the
 * allocation. Permuter candidate. */
INCLUDE_ASM(func_801F603C);
