#include "engine/slus/slus.h"

/* calls _SpuInit with 0.
 */
MATCH void SpuInit(void) {
    _SpuInit(0);
}
