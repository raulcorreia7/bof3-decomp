/* Runs the walk update: on cell 0xAF requests an area change; counts walk frames (two per frame facing 2 or 6); when the party is free and a run, enter or direction input is held, calls RUN with it; then resets the step to 0. */
/* AREA_WALK_STEP (area104 0x801F4E3C, area121 0x801F5380) */
#define AREA_WALK_STEP(RUN)                                                                                                 \
    s32 value;                                                                                                              \
    u16 value2;                                                                                                             \
    u8  value3;                                                                                                             \
    func_801C3598();                                                                                                        \
    func_801C2BEC();                                                                                                        \
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {                                                                    \
        if ((Area_GetCellCode((s32)COORD_INT(g_Task->pos.x), (s32)COORD_INT(g_Task->pos.y)) & 0xFF) == 0xAF) {              \
            Game_RequestAreaChange(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);                 \
            g_GameEntryMode   = 0;                                                                                          \
            g_GameRequestKind = 0xC;                                                                                        \
            return;                                                                                                         \
        }                                                                                                                   \
        if ((Area_GetCellCode((s32)COORD_INT(g_Task->pos.x), (s32)COORD_INT(g_Task->pos.y)) & 0xFF) == 0xC0) {              \
            func_801A0048(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));                                              \
        }                                                                                                                   \
    }                                                                                                                       \
    value2           = g_EncounterSteps;                                                                                    \
    g_EncounterSteps = value2 + 1;                                                                                          \
    value3           = g_Task->direction_08;                                                                                \
    if ((value3 == 2) || (value3 == 6)) {                                                                                   \
        g_EncounterSteps = value2 + 2;                                                                                      \
    }                                                                                                                       \
    Actor_StopMoving();                                                                                                     \
    if (func_801A79A4(g_Task->pos.x.fixed, g_Task->pos.y.fixed) == 0) {                                                     \
        func_801C329C();                                                                                                    \
        if (!(g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING)) {                    \
            value = g_Game.input & (g_InputMasks[WORLD_INPUT_RUN] | (g_InputMasks[WORLD_INPUT_ENTER] | INPUT_DIRECTIONAL)); \
            if (value != 0) {                                                                                               \
                RUN(value);                                                                                                 \
                return;                                                                                                     \
            }                                                                                                               \
        }                                                                                                                   \
        g_Game.current->u.field.mode_12B.s8_value = 0;                                                                      \
    }                                                                                                                       \
    g_Task->header.step = 0;
