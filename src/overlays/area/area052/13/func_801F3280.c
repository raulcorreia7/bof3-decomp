#include "area052_13.h"

/* two-cell column loop (Area_StoreHeight, Area_GetCellCode, Area_SetCellCode(x, y, 0x11) per row); retail keeps x, y, y+1, (y+1)<<16 and two counters in s-regs (frame 56); my loop is frame 64, 4 bytes long; first diff +0x0 */
INCLUDE_ASM(func_801F3280);
