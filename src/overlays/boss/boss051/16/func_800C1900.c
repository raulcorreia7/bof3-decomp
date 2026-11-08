#include "boss051_16.h"

/* hint: m2c draft. Loads g_BattleCurrentEnemy byte@0xE0, stores D_800E40CE[idx*0x88] to TASK_BYTES[9] in jal delay slot of Battle_AllocEffect(3,7), stores g_Task to D_801EC3A4[(u8)ret*30], increments TASK_BYTES[2]. Commutative addu operand order and delay-slot store scheduling differ. */
INCLUDE_ASM(func_800C1900);
