MATCH void func_801F32D8(void) {
    if (g_ScenarioState.scenario_id >= 8) {
        Fairy_InitVillage();
    }
    D_801455C7 = 0;
    if (g_GameCellType != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 12));
    }
}
