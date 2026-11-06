/* Advances the character's script phase: the work byte at +0x0B selects
 * idle (0), the select-and-advance step (1) or the finished-scene check
 * (anything else). A done flag clears the work marker at +0x2B and the
 * panel mode byte in the game state record. One definition shared by the
 * plchar character programs; each program includes it where the function sits.
 */
MATCH void Char_AdvanceScript(void) {
    u8 done;

    done = 0;
    if (g_Task->unk_0B != 0) {
        if (g_Task->unk_0B == 1) {
            if (func_8014DAEC() & 0xFF) {
                Actor_SelectScript(g_Task->direction_08);
                g_Task->unk_0B = 2;
            }
        } else {
            func_8014D978();
            if (D_80143BB0 == 0) {
                done = 1;
            }
        }
    } else {
        if (func_8014DAEC() & 0xFF) {
            done = 1;
        }
    }
    if (done & 0xFF) {
        g_Task->unk_2B                 = 0;
        g_GameState->mode_12B.u8_value = 0;
    }
}
