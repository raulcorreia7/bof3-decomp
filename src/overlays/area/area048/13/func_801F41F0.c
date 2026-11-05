#include "area048_13.h"

/* resume: best 2 differing (one RECT for the four halfwords fixes the dropped stores - four separate s16 locals with only &sp10 taken let the compiler drop the rest; the residual is the x/dx expansion interleave: retail splits (arg1+1)'s addiu and shift around the arg0<<6 chain, ours keeps the chains adjacent); first `!` +0x10 (sll v0 vs addiu a2); next lever: the permuter (queue behind func_801F33C0), or a statement interleave whose expansion order falls in retail order. */
INCLUDE_ASM(func_801F41F0);
