#include "area144_13.h"

/* Six-row init loop at 0x800E4816, stride 0x1C, byte stores in the order +2,+3,+1,-2,-1,0 with an unexplained 0x10-byte frame; a plain pointer loop gives no frame and a different store order (first difference addiu sp,sp,-16). */
INCLUDE_ASM(func_801F30CC);
