#include "area041_13.h"

/* Area request settle step: on flag 6 it sets the work state to 6 and the
 * x step to -0x2940, else advances the state and uses -0x2B80, then stamps
 * y/z and calls func_801F2EFC, func_801F3064. Near match with a work local
 * assigned in each branch (0x90 against retail 0xA0): retail reloads
 * g_SpadWork once more per branch tail and keeps the li 6 in the beqz delay
 * slot. First differing instruction: retail 0x801F3208 beqz v0,0x801F3230
 * against beqz v0,0x801F3220 (branch layout). Needs D_80144EA0 and the
 * func_801F2EFC/func_801F3064 declarations in the image header. */
INCLUDE_ASM(func_801F31F0);
