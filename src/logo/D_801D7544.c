/* exe/logo data at 0x801D7544 (4 bytes), embedded in .text between the
 * functions and read by DecDCTvlcSize and DecDCTvlc.  The
 * word 0x00FFFFFF is a GTE placeholder pattern, so it is stored as
 * halfwords.
 * DecDCTvlcSize is hand assembly (an addi overflow trap and a branch into the
 * next function), so it stays an asm segment and has no C source. */

#include "logo.h"

u16 D_801D7544[2] = {
    0xffff,
    0x00ff,
};
