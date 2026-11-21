#include "game_01.h"

/* The type-0 loader checks this module ID against the TOC cache before calling
 * code at base+4 (@source: wiki:formats/area#0x801f2c00-area-program-code-arena). */
u32 D_801D0C00 = 32;
