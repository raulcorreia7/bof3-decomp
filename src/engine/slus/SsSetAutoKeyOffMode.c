#include "engine/slus/slus.h"

/* stores the given byte at D_8018E98C.
 */
MATCH void SsSetAutoKeyOffMode(short mode) {
    D_8018E98C = mode;
}
