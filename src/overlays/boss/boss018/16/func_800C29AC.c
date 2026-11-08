#include "boss018_16.h"

/* hint: m2c draft. Nested 2x2 loops: dest[(D_800C2DC5[arg0*2+i] * *(u8*)0x80104000) + D_800C2DC4[arg0*2+j]] = D_800C2DC8[arg1] at 0x80104030 (word table). Fixed addresses 0x80104000/0x80104030 and loop/register order differ. */
INCLUDE_ASM(func_800C29AC);
