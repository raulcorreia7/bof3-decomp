#include "engine/slus/slus.h"

/* swaps the two 12-byte triples.
 */
/* func_8014C47C */
MATCH void MATH_SwapVectors(struct Vec3W* a, struct Vec3W* b) {
    struct Vec3W temp;

    temp = *b;
    *b   = *a;
    *a   = temp;
}
