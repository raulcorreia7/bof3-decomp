#include "area119_13.h"

/* Hand draft with the 0x18000 limit hoisted into a local differs only in one delay-slot fill: retail leaves the
 * dx-abs bgez slot at 0x801F31A0 empty and completes the limit materialization at 0x801F3194, while every tried
 * form (limit local, ternary abs, block form) sinks the ori into the slot (0x9C vs 0xA0). Permuter candidate. */
INCLUDE_ASM(func_801F3170);
