#include "area198_13.h"

/* Body: every eighth frame with g_ScriptVars[0] >= 3, play cue 0 when unk_0B is a multiple of 8, call func_801F36B4 (twice from 4 up), then rewind the script cursor by 2. First differing instruction: addiu sp,sp,-32 (retail keeps &g_ScriptVars in s0 across the calls); a u8* local and the direct array reads fold the address into each use. */
INCLUDE_ASM(func_801F3600);
