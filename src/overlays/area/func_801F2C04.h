/* One definition shared by the area overlays; every change here must verify every member. */
MATCH void func_801F2C04(void) {
    u8* record;

    record                    = (u8*)g_ScriptWorkRecord;
    g_MessageRequest          = 0xFFFF;
    FIELD(s32, record, 0x18U) = AREA_SELECTION_FIRST[D_801490C7 * 2];
    /* FAKE: retail reloads the selection after the 0x18 store. */
    MATCH_FAKE_BARRIER();
    FIELD(s32, record, 0x1CU) = AREA_SELECTION_SECOND[D_801490C7 * 2];
}
