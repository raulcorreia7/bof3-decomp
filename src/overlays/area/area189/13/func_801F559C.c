#include "area189_13.h"

/* Hint: adds task vx/vy/vz to pos.x/y/z, writes pos.x/y to
 * g_AreaScrollTargetX/Y, sets g_AreaCameraRefreshCount=2, stores pos.z last
 * (jr delay slot). Tried task pointer += form; diff from +0x0 (register/load
 * order), size 0x58 vs 0x64. */
INCLUDE_ASM(func_801F559C);
