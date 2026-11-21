#include "area118_13.h"

#include "overlays/area/shared/Area_FloorQuad.h"

#define AREA118_FLOOR_QUAD_DIRECTION_STEP 0x21
#define AREA118_FLOOR_QUAD_SPRITE_WORD    (((0x150) << 16) | 0x10F)

#ifdef NON_MATCHING
NON_MATCHING void func_801F381C(s32 sample_height) {
    AREA_DRAW_FLOOR_QUAD((g_Task->direction * AREA118_FLOOR_QUAD_DIRECTION_STEP << 16) | AREA118_FLOOR_QUAD_SPRITE_WORD);
}
#else
INCLUDE_ASM(func_801F381C);
#endif
