#include "area077_14.h"

MATCH void func_801F40D4(void) {
    if (SELF(Actor)->vx % 30 == 0) {
        SND_SEPlay(0x20B);
    }
    if (SELF(Actor)->vx % 30 < 15) {
        func_801F4B80();
    }
    if (--SELF(Actor)->vx == 0) {
        func_80196070();
    }
}
