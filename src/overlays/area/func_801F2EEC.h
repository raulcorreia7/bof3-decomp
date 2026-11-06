/* Each image header names its step table in FUNC_801F2EEC_TABLE. One definition shared by the area overlays; every change here must verify every member. */
MATCH void func_801F2EEC(void) {
    s32    x;
    s32    y;
    s32    scaled;
    Actor* scratch;

    scaled = g_BattlePartyBattlers[0].unk_0C * g_BattlePartyBattlers[0].unk_09;
    x      = (D_80145EC4[0] + scaled) >> 16;
    y      = (D_80145EC8 + g_BattlePartyBattlers[0].unk_10 * g_BattlePartyBattlers[0].unk_09) >> 16;

    scratch     = g_Task;
    scratch->vx = x;
    scratch->vy = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {
        g_Task->unk_0B = 1;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {
        g_Task->unk_0B = 2;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {
        g_Task->unk_0B = 3;
    } else if (g_AreaWalkFlags & AREA_WALK_TRANSITION) {
        g_Task->unk_0B = 4;
    } else {
        g_Task->unk_0B = 0;
    }

    FUNC_801F2EEC_TABLE[g_Task->mode]();
}
