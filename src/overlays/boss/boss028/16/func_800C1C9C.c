#include "boss028_16.h"

/* hint: the plain draft (slot header.mode = 1 and target = g_Task through g_BattleEffects[index]) is close; retail keeps the battler in v1 and the task in a1 and loads the AllocEffect argument 3 after the z read; needs g_BattleEffects alias row. */
INCLUDE_ASM(func_800C1C9C);
