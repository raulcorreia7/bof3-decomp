/* Weighted random actor spawn: picks a row from the D_801F2DCC weights, hides
 * the first eight Actor rows except the pick, places it at the
 * D_801F2DBC/D_801F2DBD coordinate pair with the Area_SampleHeight height, and
 * steps D_80143F22 from D_80145FB8. One definition shared by the five
 * world00/world01 area overlays (emi/world00/area029/13 and emi/world01/
 * area063/13, area064/13, area072/13, area073/13) at 0x801F2C04; every change
 * here must verify every member. */

s16 Area_SampleHeight(s32 x, s32 y);

extern u8  D_801468C6[];
extern u8  D_801F2DBC[];
extern u8  D_801F2DBD[];
extern u8  D_801F2DCC[];
extern s16 D_80143F22;
extern u16 D_80145FB8;

MATCH void func_801F2C04(void) {
    u8  roll;
    s32 count;
    u8  weight;
    s32 i;
    s32 pick;
    s32 offset;
    s32 y;

    roll  = rand() & 0x3F;
    count = 0;
pick_weight:
    weight = D_801F2DCC[count];
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
        pick   = rand();
        offset = count * (ACTOR_SIZE / 8);
        /* FAKE: retail keeps the nineteen-times step live across the pick
         * mask. */
        MATCH_FAKE_USE(offset);
        pick                           = (pick & 7) * 2;
        g_Actors[count].x.fixed        = D_801F2DBC[pick] << 16;
        y                              = D_801F2DBD[pick] << 16;
        g_Actors[count].y.fixed        = y;
        g_Actors[count].z.part.integer = Area_SampleHeight(g_Actors[count].x.fixed, y);
    }
    D_80143F22 = D_80145FB8 - 5;
}
