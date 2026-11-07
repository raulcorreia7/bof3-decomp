/* Move the selection cursor by four rows per flag step, then toggle the flag
 * on the cancel input and queue the matching cue. One definition shared by the
 * shop, start, Bate and Shisu overlays; each overlay includes this file where
 * the function sits.
 */
/* func_801D4BD0 (bate), func_801D5B78 (shisu), func_801DA678 (shop), func_801DDB70 (start) */
MATCH u8 Menu_ToggleOption(void) {
    s8* flag;
    u16 pad;
    u16 confirm;

    WinDrawCueText(28, 22, 0xF);
    flag = &D_8014865B;
    Menu_DrawCursorSprite((u16)(((0x1F - (*flag * 4)) * 8) + 0x1B), 0x18, 0);
    pad = g_InputPressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        *flag = 0;
        return true;
    }
    if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        confirm = 0x106;
        if (*flag != 0) {
            confirm = 0x104;
        }
        SND_PlayCue(confirm);
        return true;
    }
    if (pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        *flag = (u8)*flag ^ 1;
    }
    return false;
}
