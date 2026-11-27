MATCH s32 func_801F2C04(void) {
    Actor* record;

    record = g_ScriptWorkRecord;
    MESSAGE_REQUEST_CLEAR();
    record->unk_18 = AREA_SELECTION_FIRST[g_UIMessageChoice * 2];
    /* FAKE: retail reloads the selection after the 0x18 store. */
    FAKE_BARRIER();
    record->unk_1C = AREA_SELECTION_SECOND[g_UIMessageChoice * 2];
}
