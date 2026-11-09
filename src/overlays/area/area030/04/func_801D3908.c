#include "area030_04.h"

/* Draws the AREA030 panel header row through the shared helper at `0x801D9534`. */
MATCH void func_801D3908(void) {
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}
