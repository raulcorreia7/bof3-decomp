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
    if ((member->status.field.flags.unsigned_value & 0x01) != 0) {
        return -1;
    }

    direction = SELF(Actor)->direction;
    pos_x     = SELF(Actor)->pos.x.fixed + g_FacingSteps[direction].x;
    pos_y     = SELF(Actor)->pos.y.fixed + g_FacingSteps[direction].y;

    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (g_SpawnedActors[i].header.flags != 0 && g_SpawnedActors[i].type == ACTOR_TYPE_BLOCK) {
            if ((Actor_IsInRange(pos_x, pos_y, COORD_INT(SELF(Actor)->pos.z), 1, (Actor*)&g_SpawnedActors[i]) & BYTE_MASK) != 0 &&
                (g_SpawnedActors[i].pos.x.fixed == SELF(Actor)->pos.x.fixed || g_SpawnedActors[i].pos.y.fixed == SELF(Actor)->pos.y.fixed)) {
                return (s8)i;
            }
        }
    }
    return -1;
}
