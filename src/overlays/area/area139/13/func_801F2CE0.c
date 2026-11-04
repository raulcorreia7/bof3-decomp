#include "area139_13.h"

/* m2c draft with the 0x98000 step hoisted into a local matches the prologue and the first 38 instructions; the
 * residual is loop-body scheduling (retail stores unk_1C at 0x801F2D78 before the z + 0x100 addiu). Permuter candidate. */
INCLUDE_ASM(func_801F2CE0);
