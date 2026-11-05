#include "boss034_16.h"

/* m2c draft: 7 differing. First diff at 800C2310: retail reloads g_Task into v1 for the two halfword stores. Local PartyBattler or EnemyBattler views give other registers. Next lever: the permuter on the store block. Permuter, 10 min, best score 30: the only candidates wrap the store block in do/while(0) or add a PartyBattler temporary, and neither is kept. */
INCLUDE_ASM(func_800C22D0);
