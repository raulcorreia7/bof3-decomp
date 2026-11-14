/* Every 1024 frames, spawns a flock of up to three actors at the focus point, flying 0x400 above the ground, with one random facing of four. */
/* func_801F41BC (area016), func_801F407C (area152), func_801F40F0 (area033), func_801F4128 (area151), func_801F41BC
   (area045), func_801F41BC (area115), func_801F41D0 (area121), func_801F41EC (area087), func_801F41F4 (area065) ,
   func_801F4D1C (area088) */
MATCH void Actor_SpawnFlock(void) {
    s32  i;
    s16  count;
    s32  roll;
    u8   kind;
    u8   index;
    s16  distance;
    /* FAKE: address-taken 8-byte local reserves retail's unused vars
     * slot; the pointer itself is never dereferenced. */
    s32  coords[2];
    s32* cp;

    if (g_SceneState.flags_01 & 1) {
        Actor_Clear();
        return;
    }
    if (g_FrameCount & 0x3FF) {
        return;
    }
    i     = 0;
    cp    = coords;
    roll  = rand();
    count = roll & 3;
    /* FAKE: keep the shift inside the loop body so loop.c hoists it as a loop
     * invariant; the hoist lands after the hoisted `1` (retail `li s3,1` in the
     * blez delay slot at 0x68/0x6c, `srl s5,v1,4` at 0x70). */
    kind  = (u8)(roll & 0x33);
    if (count <= 0) {
        return;
    }
    do {
        index = Actor_FindFreeSlot();
        if (index == GAME_NONE) {
            break;
        }
        g_SpawnedActors[index].header.flags     = 1;
        g_SpawnedActors[index].type             = 0x16;
        g_SpawnedActors[index].header.mode      = 1;
        g_SpawnedActors[index].unk_06           = (u8)i;
        g_SpawnedActors[index].unk_08           = (u8)(kind >> 4);
        distance                                = Area_SampleHeight(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed) + 0x400;
        COORD_INT(g_SpawnedActors[index].pos.z) = distance;
        i++;
    } while (i < count);
}
