/* Dispatches a scene handler by position index. One definition shared by scenario overlays;
 * every change here must verify every member. */
/* Scene_DispatchByPosition (scena04 0x801FA010, scena07 0x801FDA98) */
MATCH s32 Scene_DispatchByPosition(s32 x, s32 y) {
    s8  index;
    s32 result;

    index = func_801A7AD8(&g_ScenePositionTable, 1, x, y);
    if (index >= 0) {
        SYS_DISPATCH_BYTE(g_ScenePositionDispatch, index);
        result = 1;
    } else {
        result = -1;
    }
    return result;
}
