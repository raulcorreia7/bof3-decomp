/* func_801F2C38 */
MATCH void Fishing_ShowLocation(void) {
    if (D_80143F04 == AREA_ID_CHECKPOINT_BRIDGE) {
        g_GameFlags &= 0xDFFF;
    }
}
