#include "area128_13.h"

/* Spawn position setter: x=0x4E8000, z=0, y=0x88000 when slot_index_79 == 2 else 0x4E8000, then g_SpadWork->direction_08=1. Local-constant, if/else and ternary forms keep the constant in v1/a1 or add an instruction; retail keeps it in v0 (first difference lui v0,0x4e). */
INCLUDE_ASM(func_801F3030);
