#include "boss013_16.h"

/* retail reloads g_Battle.boss_flags after the |= 4 store (no CSE) and fills the jal slot with li a0; first diff 0x800C1B7C */
INCLUDE_ASM(func_800C1B4C);
