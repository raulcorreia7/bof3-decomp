/* Runs the battle magic effect step with the script bank set. One definition shared by the bmagic
 * overlays; every change here must verify every member. */
/* func_801EFAF4 (magic004), func_801EFD20 (magic120) */
MATCH void BMagic_RunStep(void) {
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
    g_ScriptBank = BMAGIC_SCRIPT_BANK;
    SYS_DISPATCH_BYTE(BMagic_StepTable, g_Task->header.step);
    g_ScriptBank = AREA_SCRIPT_BANK;
}
