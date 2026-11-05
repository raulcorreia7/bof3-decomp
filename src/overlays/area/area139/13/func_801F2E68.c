#include "area139_13.h"

/* m2c draft with the 0x3D8000/0x440000/0x20000 constants hoisted into locals matches in multiset but not in
 * schedule (first difference at 0x801F2E70): retail keeps the 0x3D8000 lui/ori pair adjacent and splits the
 * 0x440000 materialization between the call argument and the stores. Same family as func_801F2CE0's hint.
 * Permuter candidate. */
INCLUDE_ASM(func_801F2E68);
