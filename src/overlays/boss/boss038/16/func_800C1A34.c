#include "boss038_16.h"

/* Installs the three battle hooks, sets g_BattleTargetSelector to 0x40, points g_SpadWork at D_801EB630[7] (0x801EBDD8),
 * calls func_800AFD9C, then moves g_AreaScrollTargetX/Y halfway from D_80143F24/28 to the record's coord_x_34/coord_y_38
 * and sets g_AreaCameraStep to 0x20. Tried a plain body, a work local, x/y locals and a re-read of g_SpadWork: the
 * candidate is 4 bytes short and first differs at +0x5C (retail loads the record into a1 and keeps D_80143F28 unread until
 * after the first store; the candidate hoists every load). */
INCLUDE_ASM(func_800C1A34);
