#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif
