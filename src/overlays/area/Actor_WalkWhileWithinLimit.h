/* Walks the script actor one step along facing 5 and rewinds the script cursor while its y position plus the
 * facing-5 y step is at most the limit the scene selects from `limits`. */
static inline void Area_WalkWhileWithinLimit(const u8* limits) {
    if ((u32)(g_Task->pos.y.fixed + g_FacingSteps[g_Task->direction_08 & 7].y) <= (u32)(limits[g_SceneEventSelection] << 16)) {
        g_ScriptState->unk_07 = 1;
        Area_MoveActorRoute(g_ScriptState, 5);
        g_ScriptState->cursor -= 2;
    }
}
