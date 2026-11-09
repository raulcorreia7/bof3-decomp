#include "area030_04.h"

/* Calls func_801D6A2C then writes 0x37 through the scratch-pad pointer cell at `0x1F800044` to byte offset `0x0B`. */
MATCH void func_801D6F08(void) {
    func_801D6A2C();
    g_Task->param.unk_0B = 0x37;
}
