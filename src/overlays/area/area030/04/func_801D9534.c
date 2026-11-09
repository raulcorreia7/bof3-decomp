#include "area030_04.h"

/* Draws the AREA030 window frame at the given rectangle, then the
 * inset shadow rectangle two pixels in and five pixels up. */
MATCH s32 func_801D9534(s16 frame_x, u16 frame_y, s16 frame_width, s16 frame_height, u8 frame_mode) {
    func_801D934C((u16)frame_x, frame_y, (u16)frame_width, (u16)frame_height);
    func_801D95C4((frame_x + 2), (frame_y + 2), (frame_width - 5), (frame_height - 5), frame_mode);
}
