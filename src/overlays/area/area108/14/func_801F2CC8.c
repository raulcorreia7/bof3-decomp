#include "area108_14.h"

MATCH void func_801F2CC8(void) {
    /* FAKE: unused frame, 16 bytes; pure C compiles a 24-byte frame. */
    FAKE_STACK_PADS(u8, 16);

    func_801F34B8();
    if ((func_801F3034() & BYTE_MASK) == 0) {
        g_Task->header.mode++;
    }
}
