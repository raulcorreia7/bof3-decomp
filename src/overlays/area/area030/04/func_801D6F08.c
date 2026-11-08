#include "area030_04.h"

/* Calls func_801D6A2C then writes 0x37 through the scratch-pad
 * pointer cell at `0x1F800044` to byte offset `0x0B`. */
MATCH void func_801D6F08(void) {
    u8* spad_ptr;

    func_801D6A2C();
    spad_ptr      = (u8*)g_Task;
    spad_ptr[0xB] = 0x37;
}
