#include "area128_13.h"

/* hint: m2c draft. lb g_MessageChoice, bnez->else with li 0xB in delay slot; fallthrough stores g_ScriptWorkRecord->unk_7E=0xB, g_ScriptVars[0]=0xF, j to tail with li 3; else li 8; tail sb v0 to D_80146875 (s8). GCC 2.7.2 schedules val in a0 and merges tail early. */
INCLUDE_ASM(func_801F2F84);
