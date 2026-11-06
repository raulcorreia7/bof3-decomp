#include "area108_14.h"

MATCH void func_801F2CC8(void) {
    u8* work;

    /* FAKE: unused frame, 16 bytes; pure C compiles a 24-byte frame. */
    STACK_PADS(u8, 16);

    func_801F34B8();
    if ((func_801F3034() & 0xFF) == 0) {
        work = TASK_BYTES;
        work[1]++;
    }
}
