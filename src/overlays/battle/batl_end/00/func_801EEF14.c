#include "batl_end_00.h"

/* Pool countdown: steps D_8014632C down by D_801463B0 each frame, or all at once on input, then
 * advances g_BattleUiState; func_801EF7B4 is the same body over D_80146330 and Party_AddZenny.
 * Nearest C (volatile D_801463B0 read into a u32 local first, pointer set in each arm, state
 * read before the zero store): retail keeps the step in v1 and the difference in v0 at
 * 0x801EEF58, ours swaps them; no declaration order changes it. */
INCLUDE_ASM(func_801EEF14);
