/* Runs the battle magic effect step with the script table set. */
/* func_801EFAF4 (magic004), func_801EFD20 (magic120) */
MATCH void BMagic_RunStep(void) {
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(BMagic_Steps, g_Task->header.step);
    g_Scripts = AREA_SCRIPT_TABLE;
}
