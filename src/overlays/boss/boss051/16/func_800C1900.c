#include "boss051_16.h"

/* tried: g_BattleCurrentEnemy->kind*136 into D_800E40CE, Battle_AllocEffect(3,7),
 * store g_Task to D_801EC3A4[slot*120]; register allocation off (addu operands,
 * extra insns) and D_801EC3A4/D_800E40CE typing/indexing need matching */
INCLUDE_ASM(func_800C1900);
