#include "engine/slus/slus.h"

/* loads the word at record-table entry D_80146488 offset 0x30 and
 * passes it to LZ77_DecodeBegin, then calls func_8016327C.
 * The subtract-of-negated-offset form is load-bearing: retail's
 * `addu v1,v1,v0` needs the pointer as the first operand after folding.
 */
MATCH void EMI_DecompressSector(void) {
    s8* rec;

    rec = &D_80146488;
    /* FAKE: subtract-of-negated-offset keeps the pointer as the first
     * addu operand. */
    rec = rec - (rec[0] * -4);
    LZ77_DecodeBegin(*(u8**)(rec + 0x30));
    EMI_CopySectorToScratchpad();
}
