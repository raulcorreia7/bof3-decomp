#include "area135_14.h"

/* first differing instruction: lui v1,SP (retail) against lui a1,SP (candidate); retail reloads D_80147C54 and D_80147C58 in each branch of the g_SpadWork != D_80143F48 test, candidate shares the loads and is 0x70 bytes against 0x7C */
INCLUDE_ASM(func_801F4464);
