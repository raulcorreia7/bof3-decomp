#include "batl_end_00.h"

/* Pool countdown: steps D_8014632C down by D_801463B0 each frame (or all at once on input) and
 * advances g_BattleUiState. Nearest C (pointer per arm): retail loads D_801463B0 (lui/lhu v1)
 * before the D_8014632C word (lw a0) at 0x801EEF58; the scheduler puts the lw first. */
INCLUDE_ASM(func_801EEF14);
