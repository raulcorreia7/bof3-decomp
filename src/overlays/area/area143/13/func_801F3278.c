#include "area143_13.h"

/* nonmatching: 1 differing at +0x44, retail move a1,s0 against candidate move a1,zero (m2c draft of the clamp arg).
 * resume: the copy var_a1 = var_s0 after var_s0 = 0 folds to a constant in every pure-C shape tried (pre-if plus then,
 * if-else in both branches, and the typed g_SpadWork->z.fixed body with the literal copy; permuter from the typed base
 * 40k iterations, best score 25); MATCH_FAKE_OPAQUE(var_s0) between the clamp and
 * the copy is byte-exact (140 bytes, 35 instructions) but is a quality-gated harmful helper. */
INCLUDE_ASM(func_801F3278);
