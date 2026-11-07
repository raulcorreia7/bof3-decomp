#include "area134_13.h"

/* blocker: the draft swaps g_Task around its reads; retail reads *D_801468BC before the first g_Task store; first diff: lui v0 at 0x801F34E8. */
INCLUDE_ASM(func_801F3D88);
