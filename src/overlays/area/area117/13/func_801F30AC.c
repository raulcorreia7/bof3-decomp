#include "area117_13.h"

/* Hand draft matches except the beqz delay slot at 0x801F30C4: retail fills it with the lui half of the
 * D_80104000 address materialization and lands the tail at 0x801F3134, while every tried form (global spelling,
 * pointer local) leaves the slot empty and runs one instruction longer. Permuter candidate. */
INCLUDE_ASM(func_801F30AC);
