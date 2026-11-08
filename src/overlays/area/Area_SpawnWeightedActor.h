typedef struct AreaSpawnPosition {
    u8 x;
    u8 y;
} AreaSpawnPosition;

ASSERT_SIZE(AreaSpawnPosition, 2);
ASSERT_OFFSET(AreaSpawnPosition, x, 0);
ASSERT_OFFSET(AreaSpawnPosition, y, 1);

extern u16               D_80145FB8;
extern AreaSpawnPosition g_AreaSpawnPositions[];
extern u8                g_AreaSpawnWeights[];

MATCH void Area_SpawnWeightedActor(void) {
    u8  roll;
    s32 count;
    u8  weight;
    s32 i;
    s32 pick;
    s32 y;

    roll  = RANDOM_MASK(0x3F);
    count = 0;
pick_weight:
    weight = g_AreaSpawnWeights[count];
    if (roll >= weight) {
        count += 1;
        roll -= weight;
        if (count < 8) {
            goto pick_weight;
        }
    }
    for (i = 0; i < 8; i++) {
        if (i != count) {
            g_Actors[i].header.flags = 0;
        }
    }
    if (count < 8) {
        pick                             = rand();
        g_Actors[count].pos.x.fixed      = g_AreaSpawnPositions[pick & 7].x << 16;
        y                                = g_AreaSpawnPositions[pick & 7].y << 16;
        g_Actors[count].pos.y.fixed      = y;
        COORD_INT(g_Actors[count].pos.z) = Area_SampleHeight(g_Actors[count].pos.x.fixed, y);
    }
    D_80143F22 = D_80145FB8 - 5;
}
