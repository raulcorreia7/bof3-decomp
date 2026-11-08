#include "boss051_16.h"

/* tried: g_BattleCurrentEnemy->kind*136 into battle event data, Battle_AllocEffect(3,7),
 * store g_Task to the template stats table [slot*120]; register allocation off
 * (addu operands, extra insns) and table typing/indexing need matching */
INCLUDE_ASM(func_800C1900);
