#include "area037_13.h"

/* state switch like area169 func_801F390C (state = &g_SceneEventStep, flags at state + 0x63C); retail keeps &g_GameStateIndex in s1 for case 1 and shares one step store; my forms leave the frame 24 or the tail 0xC bytes long; first diff +0x0 */
INCLUDE_ASM(func_801F38DC);
