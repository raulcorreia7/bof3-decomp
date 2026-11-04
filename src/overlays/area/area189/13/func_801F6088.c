#include "area189_13.h"

/* first differing instruction: retail opens with addiu sp,-8 and a pointer-bounded loop over g_Characters[0..6] (current_hp -= min((base_hp + 25) / 50, current_hp - 1)); index and pointer forms leave an extra counter, candidate 0x7C or 0x88 bytes against 0x80 */
INCLUDE_ASM(func_801F6088);
