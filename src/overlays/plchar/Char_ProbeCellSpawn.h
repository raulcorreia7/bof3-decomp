/* The cell probe of the plchar programs that react to map cells 0xF2 and 0xF8 with the shared Char_SpawnActor: 0xF2 spawns a field record (and sometimes a second) and 0xF8 hands out the item 0x56. */
MATCH s32 Char_ProbeCellSpawn(s16 x, s16 y) {
    s32 cell;
    s32 i;
    u32 roll;
    s32 spawn_cue;
    u8* record;

    cell = Area_GetCellCode(x, y) & BYTE_MASK;
    if (cell == 0xF2) {
        if ((Actor_FindFreeSlot() & BYTE_MASK) != GAME_NONE) {
            Char_SpawnActor(0, x, y);
            roll = RANDOM_MASK(0xF);
            if (roll >= 13) {
                spawn_cue = 5;
                if (roll < 15) {
                    spawn_cue = 2;
                }
                if ((g_GameRequestFlags & 6) && !(RANDOM_MASK(3))) {
                    spawn_cue = (spawn_cue & BYTE_MASK) * CHAR_SPAWN_CUE_SCALE;
                }
                Game_RewardZenny(spawn_cue & BYTE_MASK);
                Char_SpawnActor(1, x, y);
            }
            g_Task->param.unk_0B = 1;
        }
        Area_ClearCell(x, y);
        return 1;
    }
    if (cell == 0xF8) {
        Char_SpawnActor(0, x, y);
        record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_HORSERADISH);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = record[i];
        }
        D_801490E4[0] = 0;
        if (Item_Add(ITEM_CAT_ITEM, ITEM_HORSERADISH, 1, 0) & BYTE_MASK) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            Message_Request(2);
        } else {
            Message_Request(3);
        }
        g_GameStateIndex     = GAME_REQUEST_MESSAGE;
        g_Task->param.unk_0B = 1;
        Area_ClearCell(x, y);
        return 1;
    }
    return 0;
}
