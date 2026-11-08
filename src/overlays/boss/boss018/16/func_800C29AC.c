#include "boss018_16.h"

/* tried: typed map/cell records with do/for loops, grouped columns and FIELD plus a row barrier; first diff 0x800C29B0: lui t1,0x8010 instead of sll a0,a0,1; source address hoists out of the row loop. */
INCLUDE_ASM(func_800C29AC);
