#include "area124_13.h"

/* Weighted random actor spawn: /
 * Area_SpawnWeightedActor.h with this image's table addresses - weights at
 * D_801F2DD8, the coordinate pair at D_801F2DC8/D_801F2DC9. */

extern u8  D_801F2DC8[];
extern u8  D_801F2DC9[];
extern u8  D_801F2DD8[];
extern s16 D_80143F22;
extern u16 D_80145FB8;

s16 Area_SampleHeight(s32 x, s32 y);

MATCH void Area_SpawnWeightedActor(void) {
    u8  roll;
    s32 count;
    u8  weight;
    s32 i;
    s32 pick;
    s32 y;

    roll  = rand() & 0x3F;
    count = 0;
pick_weight:
    weight = D_801F2DD8[count];
    if (roll >= weight) {
        count += 1;
        roll -= weight;
        if (count < 8) {
            goto pick_weight;
        }
    }
    for (i = 0; i < 8; i++) {
        if (i != count) {
            g_Actors[i].flags_00 = 0;
        }
    }
    if (count < 8) {
        pick                           = rand();
        g_Actors[count].x.fixed        = D_801F2DC8[(pick & 7) * 2] << 16;
        y                              = D_801F2DC9[(pick & 7) * 2] << 16;
        g_Actors[count].y.fixed        = y;
        g_Actors[count].z.part.integer = Area_SampleHeight(g_Actors[count].x.fixed, y);
    }
    D_80143F22 = D_80145FB8 - 5;
}
