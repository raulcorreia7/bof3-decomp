#include "area002_09.h"

/* Selector + flag-pointer body. Best 6 differing (direct reads + a held
 * compare constant + the flag-pointer note reproduces everything but the
 * state/value rotation: state retail v1 against a0, value retail v0 against
 * v1 from 0x801F2C08). Alternate form: an s8 state local + the constant local
 * gets state v1 and value v0 right, but swaps the head (li before the state
 * load) and leaves the constant in a0. Next lever: permuter across the two
 * forms; same trap as world04 selector rows. */
INCLUDE_ASM(func_801F2C04);
