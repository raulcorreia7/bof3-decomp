#include "area140_13.h"

/* m2c draft differs only in the dx-abs delay slot: retail leaves the bgez slot empty (nop at 0x801F2DB0) and
 * materializes the 0x8000 compare constant after the join, while every tried form fills the slot or moves the
 * work-pointer allocation (if/else abs, ABS macro, MATCH_FAKE_BARRIER after the abs). Resume with the permuter. */
INCLUDE_ASM(func_801F2D80);
