#include "area098_13.h"

/* Effect-row step taking a row pointer: sets D_801F6514 once, then steps byte +2 down, +3 down by 8, word +8 up by 0x400, word +0x10 by the new +8, clears byte 0 at zero. Needs a row type with words at +8 and +0x10 (Actor has direction_08 at +8); not tried. */
INCLUDE_ASM(func_801F4FEC);
