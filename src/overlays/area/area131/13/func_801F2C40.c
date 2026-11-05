#include "area131_13.h"

/* Hand draft matches the store sequence and the value select, but retail keeps one unfilled delay slot: the nop
 * after the last g_ScriptWorkRecord reload (0x801F2CB4) with the 0xC request in the j delay (0x801F2CC0). Every
 * tried form (stores in both arms, request local, swapped arms) fills the slot with the unk_7E store and runs one
 * instruction shorter. Permuter candidate. */
INCLUDE_ASM(func_801F2C40);
