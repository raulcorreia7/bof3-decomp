#include "area114_13.h"

/* Hint: call-seq sets g_SceneEventMode=0x2C, g_SceneEventStep=0,
 * g_SceneEventSelection=0xD after Game_SetScriptActive(), returns 0. GCC picks
 * v0 for both constants (0x2C,0xD); retail uses v1. Tried temp reuse and
 * literal forms; first diff li v1/v0 at 0x801F2C78. */
INCLUDE_ASM(func_801F2C68);
