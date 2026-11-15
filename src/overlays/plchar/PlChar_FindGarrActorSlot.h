/* Finds the actor slot for Garr's follower reach check; verify every image after a change. */
MATCH s8 PlChar_FindGarrActorSlot(void) {
    PartyMember* member;
    s32          direction;
    s32          i;
    s32          pos_x;
    s32          pos_y;

    member = g_GameState;
    if (member->chr.character_id != CHAR_ID_GARR) {
        return -1;
    }
    if ((member->status.field.flags_12C.u8_value & 0x01) != 0) {
        return -1;
    }

    direction = g_Task->direction_08;
    pos_x     = g_Task->pos.x.fixed + g_FacingSteps[direction].x;
    pos_y     = g_Task->pos.y.fixed + g_FacingStepY[direction * 2];

    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (g_SpawnedActors[i].header.flags != 0 && g_SpawnedActors[i].type == 0x30) {
            if ((func_801BDD58(pos_x, pos_y, COORD_INT(g_Task->pos.z), 1, (Actor*)&g_SpawnedActors[i]) & BYTE_MASK) != 0 &&
                (g_SpawnedActors[i].pos.x.fixed == g_Task->pos.x.fixed || g_SpawnedActors[i].pos.y.fixed == g_Task->pos.y.fixed)) {
                return (s8)i;
            }
        }
    }
    return -1;
}
