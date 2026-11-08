#include "area191_13.h"

/* hint: restores flagged characters (status 0, hp/ap = max) then copies g_Characters rows into g_Game.members[].chr; retail copies each record with a 0x10-stride loop (0x130 bytes), the struct assignment compiles to 0x104 */
INCLUDE_ASM(func_801F3AB0);
