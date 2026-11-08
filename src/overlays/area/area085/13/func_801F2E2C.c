#include "area085_13.h"

/* hint: m2c draft. Increments TASK_BYTES[2]; if==5 increments g_ScriptVars[0] and val=4 else val=(val&1)+1; stores val to TASK_BYTES[1] in Area_DrawScreenTint jal delay slot; calls func_801F2FCC. Scratchpad pointer reloads and delay-slot store scheduling differ. */
INCLUDE_ASM(func_801F2E2C);
