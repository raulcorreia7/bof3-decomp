#include "area134_13.h"

/* Best 4 differing: a pointer local `flag = &D_80146865` reproduces the a0
 * pointer, the stores and every reload. First ! row at 0x801F3CFC: the 0x17
 * set block's reload and constant land in v1/v0 against retail's v0/v1, while
 * the twin 0xD block at 0x801F3CBC matches. Next lever: permuter on the
 * set-block register rotation. */
INCLUDE_ASM(func_801F3C98);
