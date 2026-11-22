#ifndef GAME_SCRIPT_H
#define GAME_SCRIPT_H

#include "types.h"

/* The operand bits that select one of the four script variables. */
#define SCRIPT_VAR_MASK  0x0C
#define SCRIPT_VAR_SHIFT 2

typedef u8 (*ScriptOpCallback)(u8** cursor);

/* The script variable bytes at 0x80146864. */
extern u8  g_ScriptVars[4];
/* The same four bytes as one word. */
extern u32 g_ScriptVarsWord;

/* The four bytes and the word as one record: a store through it is a member store. */
typedef union {
    u8  bytes[4];
    u32 word;
} ScriptVarsRecord;

/* The script variable that holds the scene's choice. */
#define SCRIPT_VAR_CHOICE 0

/* Zero every script variable except the scene's choice. */
#define SCRIPT_VARS_CLEAR_EXCEPT_CHOICE() \
    g_ScriptVars[1] = 0;                  \
    g_ScriptVars[2] = 0;                  \
    g_ScriptVars[3] = 0

/* Zero every script variable, the scene's choice included. */
#define SCRIPT_VARS_CLEAR_ALL()          \
    g_ScriptVars[SCRIPT_VAR_CHOICE] = 0; \
    SCRIPT_VARS_CLEAR_EXCEPT_CHOICE()

#endif
