#include "area056_13.h"

/* resume: best 6 differing (the empty bnez delay slot is the extra 4 bytes: retail sinks the prologue into the lb shadow and the branch slot after hoisting the g_MessageRequest store above it; our build keeps the prologue first); first `!` +0x00 (li v0,0xffff vs addiu sp); next lever: a suffix shape whose scheduling hoists the store above the prologue - the same-image twin func_801F3194 compiles the opposite prefix order from the same prefix source, so the trigger is the SND_PlayCue-first nested body; else the permuter. */
INCLUDE_ASM(func_801F3200);
