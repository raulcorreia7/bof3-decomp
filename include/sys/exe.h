#ifndef SYSTEM_EXE_H
#define SYSTEM_EXE_H

#include "types.h"

extern u8 g_PartyFieldOrder[];

/* Forwards the selector byte to func_8014D6DC with a zero extra operand. */
/* Claims a free field record and fills its header; returns the slot, or 0xFF when none is free. */
s32 func_8015CB18();
/* Draws a four-strip textured panel fill. */

#endif
