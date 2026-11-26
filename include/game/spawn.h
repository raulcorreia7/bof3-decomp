#ifndef GAME_SPAWN_H
#define GAME_SPAWN_H

#include "types.h"
#include "sys/scratchpad.h"

/* The scratchpad base shared by the entity-spawn routines of the game and
 * world overlays. A unit that reads it as plain bytes defines
 * FAKE_DECL_GAME_SCRATCH_BASE_SCALAR before its first include and takes the byte array;
 * the ScratchPad record is the default. A use that needs another width keeps a
 * FAKE: cast. */
#ifdef FAKE_DECL_GAME_SCRATCH_BASE_SCALAR
extern u8 g_ScratchPad[];
#elif defined(FAKE_DECL_GAME_SCRATCH_BASE_WORD)
extern s32 g_ScratchPad;
#else
extern ScratchPad g_ScratchPad;
#endif

#endif
