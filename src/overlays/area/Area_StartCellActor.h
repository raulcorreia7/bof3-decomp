/* Clears the actor for pajama Ryu or when scene flag 1 is set; otherwise loads scene record 0x205, resets the actor's work bytes and sets cell code 0xA0 at the x and y that the row (0x0B) names in the tables CELL_X and CELL_Y. */
/* AREA_START_CELL_ACTOR (area087 0x801F4640, area088 0x801F5170, area121 0x801F4624) */
#define AREA_START_CELL_ACTOR(CELL_X, CELL_Y)                                                              \
    s32 row_offset;                                                                                        \
    s32 map_offset;                                                                                        \
    if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (g_SceneState.flags_01 & 1)) { \
        Actor_Clear();                                                                                     \
        return;                                                                                            \
    }                                                                                                      \
    Game_FindArea();                                                                                \
    Area_SelectSceneRecord(0x205);                                                                         \
    g_Task->unk_48       = 0;                                                                              \
    g_Task->active_flags = 0;                                                                              \
    g_Task->unk_2A       = 0;                                                                              \
    ACTOR_CLEAR_TINT();                                                                                    \
    row_offset                                           = g_Task->param.unk_0B * 4;                       \
    map_offset                                           = CELL_Y[row_offset] * g_AreaMapBundle.width;     \
    *(g_AreaCellCodes + map_offset + CELL_X[row_offset]) = 0xA0;                                           \
    Actor_SelectScript(0);                                                                                 \
    g_Task->header.mode = 1;
