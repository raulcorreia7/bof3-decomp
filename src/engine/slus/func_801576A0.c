#include "engine/slus/slus.h"

/* keeps the low 24 bits of the word at record and forces its top byte to 0x23. */
MATCH void func_801576A0(u32* record) {
    u32 word;

    SLUS_RETAG_BUNDLE_AND_RUN(0x23000000);
}
