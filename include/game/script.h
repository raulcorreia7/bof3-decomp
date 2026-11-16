#ifndef GAME_SCRIPT_H
#define GAME_SCRIPT_H

#include "types.h"

/* The operand bits that select one of the four script variables. */
#define SCRIPT_VAR_MASK  0x0C
#define SCRIPT_VAR_SHIFT 2

typedef u8 (*ScriptFunc)(u8** cursor);

/* The script variable bytes at 0x80146864. */
extern u8  g_ScriptVars[4];
/* The same four bytes as one word. */
extern u32 g_ScriptVarsWord;

#endif
