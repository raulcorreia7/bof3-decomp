#include "area134_13.h"

/* nonmatching 4 differing (body 0xA4 against 0x9C): D_80146865 is u8 (retail li v0,255/254, the s8 draft folds to -1/-2)
 * and D_80146144 must live in a local used by both the compare and the call (retail keeps it in a0 from +0x40). resume:
 * that local also has to keep the compare constant in v0 (a step local before it flips the order to v1 at +0x4). */
INCLUDE_ASM(func_801F3440);
