#include "area111_13.h"

/* first differing instruction: srl v1,v1,3 (retail) against sra (candidate) in the exact division of g_CurrentActor - D_80147A58 (D_80147A58 is one row past the 30-row actor table); the rest of if (D_80146867 != (0x10 << (g_CurrentActor - D_80147A58))) { g_ScriptState->cursor -= 2; } matches; signed and unsigned casts tried */
INCLUDE_ASM(func_801F3790);
