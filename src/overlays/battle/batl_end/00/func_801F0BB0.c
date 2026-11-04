#include "batl_end_00.h"

/* Experience still missing for the next level: the sum of g_LevelGrowth[id][0..level].exp minus
 * g_Characters[id].exp, 0 when the sum is not above it (func_801F07E0 prints it). Draft: u32
 * needed, u8 id, flat index [id * LEVEL_GROWTH_LEVEL_COUNT + (level & BYTE_MASK)], do-while.
 * First difference at 0x801F0BE8: retail masks the id into a2 and the level into a0, ours puts
 * the id in a0. */
INCLUDE_ASM(func_801F0BB0);
