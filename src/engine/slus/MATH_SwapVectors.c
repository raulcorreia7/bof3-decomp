#include "engine/slus/slus.h"

/* swaps the two 12-byte triples.
 */
/* func_8014C47C */
MATCH void MATH_SwapVectors(Pos3* a, Pos3* b) {
    Pos3 temp;

    temp = *b;
    *b   = *a;
    *a   = temp;
}
