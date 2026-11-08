#include "area149_13.h"

/* hint: two-slot spawn loop; the 0x194 draft with ActorSlot unk_2C (needs a u16 at +0x2C) is 12 bytes over, retail copies the raw slot into a1 where ours masks (first diff +0x48) */
INCLUDE_ASM(func_801F3140);
