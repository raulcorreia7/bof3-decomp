#include "area030_04.h"

/* Submits the two AREA030 panel updates at the requested vertical
 * positions after selecting graphics mode 0. */
MATCH void func_801E0ED0(s16 panel_x, s16 panel_y) {
    func_801E0C80(0, 1);
    func_801E0DCC(0, 1, (panel_x + 8), panel_y);
    func_801E0DCC(1, 1, (panel_x + 0x108), panel_y);
}
