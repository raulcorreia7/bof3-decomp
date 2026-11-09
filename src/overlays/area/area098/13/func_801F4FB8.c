#include "area098_13.h"

/* Step a countdown byte: decrement it, and when it reaches zero reload it and
 * advance the step byte. */
MATCH void func_801F4FB8(u8* p) {
    p[2]--;
    if (p[2] == 0) {
        p[2] = 0x10;
        p[1]++;
    }
}
