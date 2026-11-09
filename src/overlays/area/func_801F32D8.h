MATCH void func_801F32D8(void) {
    if (g_SceneState.scenario_id >= 8) {
        Fairy_InitVillage();
    }
    D_801455C7 = 0;
    if (D_80143F03 != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 12));
    }
}
