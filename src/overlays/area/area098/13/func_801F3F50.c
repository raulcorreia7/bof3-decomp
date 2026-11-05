#include "area098_13.h"

/* Best: structure exact, 9 differing rows one register rotation (reload retail
 * v1 against v0, step/next chain retail v0 against v1) from 0x801F3F78. Tried
 * u16/s32 next and a matched-mode return (copy stays). Next lever: permuter on
 * the register rotation, or a form that frees v0 before the post-call reload. */
INCLUDE_ASM(func_801F3F50);
