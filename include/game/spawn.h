#ifndef GAME_SPAWN_H
#define GAME_SPAWN_H

#include "types.h"
#include "sys/scratchpad.h"

/* The scratchpad base shared by the entity-spawn routines of the game and
 * world overlays. A unit that reads it as plain bytes defines
 * GAME_SCRATCH_BASE_SCALAR before its first include and takes the byte array;
 * the ScratchPad record is the default. A use that needs another width keeps a
 * FAKE: cast. */
#ifdef GAME_SCRATCH_BASE_SCALAR
extern u8 D_1F800000[];
#elif defined(GAME_SCRATCH_BASE_WORD)
extern s32 D_1F800000;
#else
extern ScratchPad D_1F800000;
#endif
/* Id byte column of the 0x98-byte entity work rows. */
extern u8 D_8014691A[];

#endif
