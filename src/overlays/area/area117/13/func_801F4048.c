#include "area117_13.h"

/* tried: none (skipped - switch/jump table jtbl_801F2C04 mapping unknown, D_801F55E4 in blob);
 * needs D_801F55E4 (u16[6]) and switch on g_MessageChoice < 6: cases set
 * g_ScriptVars[0]=0xA + SND_PlayCue(0x205), or g_ScriptVars[0]=0x14, per jtbl */
INCLUDE_ASM(func_801F4048);
