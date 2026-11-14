/* Dispatches a scene handler by position index. */
/* func_801FA010 (scena04), func_801FDA98 (scena07) */
MATCH s32 Scene_DispatchByPosition(s32 x, s32 y) {
    s8  index;
    s32 result;

    index = func_801A7AD8(&g_ScenePositions, 1, x, y);
    if (index >= 0) {
        SYS_DISPATCH_BYTE(g_ScenePositionDispatch, index);
        result = 1;
    } else {
        result = -1;
    }
    return result;
}
