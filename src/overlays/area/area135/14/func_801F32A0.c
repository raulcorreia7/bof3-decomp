#include "area135_14.h"

/* Hint: copies D_80147A8C/g_AreaFocusY/D_80147A94 to task pos.x/y/z, sets
 * g_AreaHeightOffsetEnabled=1, stores D_80147A94 to pos.z in Area_ReadHeight
 * delay slot, stores (height<<16) to vz (0x14). Tried direct copies; diff at
 * +0x10 (load order), delay-slot pos.z store needed. */
INCLUDE_ASM(func_801F32A0);
