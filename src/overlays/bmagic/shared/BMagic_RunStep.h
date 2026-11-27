/* Runs the battle magic effect step with the script table set. */
/* func_801EFAF4 (magic004), func_801EFD20 (magic120) */
MATCH void BMagic_RunStep(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(BMagic_Steps, SELF(PartyMember)->header.step);
    g_Scripts = AREA_SCRIPT_TABLE;
}
