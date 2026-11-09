#include "engine/slus/slus.h"

/* keeps the low 24 bits of the word at record and forces its top byte to 0x25. */
MATCH void func_80157644(u32* record) {
    u32 word;

    SLUS_RETAG_BUNDLE_AND_RUN(0x25000000);
}
