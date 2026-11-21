typedef Cell2 AreaSpawnCell;

ASSERT_OFFSET(AreaSpawnCell, x, 0);
ASSERT_OFFSET(AreaSpawnCell, y, 1);
ASSERT_SIZE(AreaSpawnCell, 2);

extern u16           D_80145FB8;
extern AreaSpawnCell g_AreaSpawnPositions[];
extern u8            g_AreaSpawnWeights[];

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
    g_EncounterSteps = D_80145FB8 - 5;
}
