#ifndef GAME_SPAWN_H
#define GAME_SPAWN_H

#include "types.h"
#include "sys/scratchpad.h"

/* The scratchpad base shared by the entity-spawn routines of the game and
 * world overlays. A unit that reads it as one word defines
 * FAKE_DECL_GAME_SCRATCH_BASE_WORD before its first include and takes the scalar;
 * the ScratchPad record is the default. */
#if defined(FAKE_DECL_GAME_SCRATCH_BASE_WORD)
extern s32 g_ScratchPad;
#else
extern ScratchPad g_ScratchPad;
#endif

#endif
