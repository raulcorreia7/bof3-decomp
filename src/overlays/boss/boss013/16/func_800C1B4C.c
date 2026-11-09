#include "boss013_16.h"

/* retail reloads g_Battle.boss_flags after the |= 4 store (no CSE) and fills the jal slot with li a0. */
INCLUDE_ASM(func_800C1B4C);
