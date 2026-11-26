/* Runs the walk update: on cell 0xAF requests an area change; counts walk frames (two per frame facing 2 or 6); when the party is free and a run, enter or direction input is held, calls RUN with it; then resets the step to 0. */
/* AREA_WALK_STEP (area104 0x801F4E3C, area121 0x801F5380) */
#define AREA_WALK_STEP(RUN)                                                                                                 \
    s32 value;                                                                                                              \
    u16 value2;                                                                                                             \
    u8  value3;                                                                                                             \
    Party_TickConfusion();                                                                                                  \
    Party_FloorDamageUpdate();                                                                                              \
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {                                                                    \
        if ((Area_CellGetCode((s32)COORD_INT(TASK(Actor)->pos.x), (s32)COORD_INT(TASK(Actor)->pos.y)) & 0xFF) == 0xAF) {    \
            Game_RequestAreaChange(g_GameEntryAreaId, g_GameEntryPosX, g_GameEntryPosY, g_GameEntryFacing);                 \
            g_GameEntryMode   = 0;                                                                                          \
            g_GameRequestType = 0xC;                                                                                        \
            return;                                                                                                         \
        }                                                                                                                   \
        if ((Area_CellGetCode((s32)COORD_INT(TASK(Actor)->pos.x), (s32)COORD_INT(TASK(Actor)->pos.y)) & 0xFF) == 0xC0) {    \
            Area_RequestLinkAtCell(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));                           \
        }                                                                                                                   \
    }                                                                                                                       \
    value2           = g_EncounterSteps;                                                                                    \
    g_EncounterSteps = value2 + 1;                                                                                          \
    value3           = TASK(Actor)->direction;                                                                              \
    if ((value3 == 2) || (value3 == 6)) {                                                                                   \
        g_EncounterSteps = value2 + 2;                                                                                      \
    }                                                                                                                       \
    Actor_StopMoving();                                                                                                     \
    if (func_801A79A4(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) == 0) {                                           \
        func_801C329C();                                                                                                    \
        if (!(g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING)) {                    \
            value = g_Game.input & (g_InputMasks[WORLD_INPUT_RUN] | (g_InputMasks[WORLD_INPUT_ENTER] | INPUT_DIRECTIONAL)); \
            if (value != 0) {                                                                                               \
                RUN(value);                                                                                                 \
                return;                                                                                                     \
            }                                                                                                               \
        }                                                                                                                   \
        g_Game.current->u.field.mode.value = 0;                                                                             \
    }                                                                                                                       \
    TASK(Actor)->header.step = 0;
