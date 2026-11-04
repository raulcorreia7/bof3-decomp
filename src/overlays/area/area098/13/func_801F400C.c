#include "area098_13.h"

/* first differing instruction: lui v1,0x1f80 (retail) against lui v0 (candidate); the body is the s16 counter at +0x30 ramped to a fade level and the u16 counter at +0x2E that calls Actor_Clear at zero, but retail reads +0x30 with lhu and compares the incremented value as s16, a width the Actor.unk_30 member lacks (needs: type). Pre-increment, locals and a clamp local tried. */
INCLUDE_ASM(func_801F400C);
