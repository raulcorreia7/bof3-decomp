#include "area134_13.h"

/* first differing instruction: lui v0 (retail) against lui v1 (candidate) at the g_Actors[0].x load. Body: save g_SpadWork, point it at g_Actors, compare g_Actors[0].x with D_80145EC4, g_GameState = g_BattlePartyBattlers, store the saved work pointer back three times (the middle one g_BattlePartyBattlers), then step 4 or (0xD and unk_09 = 0); the stores are kept by retail, plain and SP_REF forms drop or reorder them */
INCLUDE_ASM(func_801F2EBC);
