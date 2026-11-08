#include "boss025_13.h"

/* blocker: retail reloads g_BattleCurrentEnemy and D_80144E00 in its own registers after the call; first diff: lui v1 at 0x800C1C18. */
INCLUDE_ASM(func_800C1BB0);
