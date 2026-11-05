#include "area030_04.h"

/* Queues the two AREA030 icon strip primitives for the selected mode. */
MATCH void func_801D2034(s16 strip_x, s16 strip_y, u8 icon_mode, s32 icon_count) {
    func_801E0C80(0, icon_mode);
    func_801E0DCC(0x17, icon_mode, strip_x, strip_y);
    func_801E0DCC((u8)(icon_count + 0x17), icon_mode, (strip_x + 0x28), strip_y);
}
