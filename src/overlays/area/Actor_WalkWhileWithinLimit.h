/* Walks the script actor one step along facing 5 and rewinds the script cursor
 * while its y position plus the facing-5 y step is at most the limit the scene
 * selects. One definition shared by the world area overlays; each image names its
 * limit table AREA_WALK_LIMIT_TABLE. Every change here must verify every member
 * address. */
/* func_801F2D68 (area136), func_801F4840 (area188) */
MATCH void Actor_WalkWhileWithinLimit(void) {
    if ((u32)(g_SpadWork->y.fixed + g_FacingSteps[g_SpadWork->direction_08 & 7].y) <=
        (u32)(AREA_WALK_LIMIT_TABLE[D_801448ED] << 16)) {
        g_ScriptState->unk_07 = 1;
        func_801ABBA8(g_ScriptState, 5);
        g_ScriptState->cursor -= 2;
    }
}
