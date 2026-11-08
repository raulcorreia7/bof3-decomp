/* Checks the step trigger at (x, y): a step into the trigger band with the scene ready clears the first script
 * variable and runs script entry 0, which starts the area scene and blocks the step. Each member passes the
 * band's first row. One definition shared by the area overlays; every change here must
 * verify every member. */
/* func_801F2C64 (area036), func_801F2DB4 (area116), func_801F2E80 (area059) */
#define AREA_CHECK_STEP_TRIGGER(first_row)                                                                 \
    MATCH s32 Area_CheckStepTrigger(s32 x, s32 y) {                                                        \
        if (D_80143F03 == 2 && SYS_TestFlag(g_SceneEventFlags, 0x33) != 0 && (u32)((x >> 16) - 70) < 3U) { \
            if ((u32)((y >> 16) - first_row) < 3U && (g_BattlePartyBattlers[0].facing == FACING_UP_LEFT || \
                                                      (u32)(g_BattlePartyBattlers[0].facing - 6) < 2U)) {  \
                *g_ScriptVars = 0;                                                                         \
                func_801BE1B0(0);                                                                          \
                return 1;                                                                                  \
            }                                                                                              \
        }                                                                                                  \
        return 0;                                                                                          \
    }
