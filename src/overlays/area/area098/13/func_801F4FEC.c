#include "area098_13.h"

/* Effect-row step taking a row pointer: sets D_801F6514 once, then steps byte +2 down, +3 down by 8, word +8 up by 0x400, word +0x10 by the new +8, clears byte 0 at zero. Actor has direction_08, unk_09, unk_0A and unk_0B at +8, so the word needs a union over those four byte members and a rename of every user of them; not done. */
INCLUDE_ASM(func_801F4FEC);
