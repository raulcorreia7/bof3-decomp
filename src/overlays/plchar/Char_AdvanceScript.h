/* Advances the character's script phase: the work byte at +0x0B selects idle (0), the select-and-advance step (1) or the finished-scene check (anything else). A done flag clears the work marker at +0x2B and the panel mode byte in the game state record. */
MATCH void Char_AdvanceScript(void) {
    u8 done;

    done = 0;
    if (g_Task->param.unk_0B != 0) {
        if (g_Task->param.unk_0B == 1) {
            if (Actor_StepAnimOnce() & BYTE_MASK) {
                Actor_SelectScript(g_Task->direction_08);
                g_Task->param.unk_0B = 2;
            }
        } else {
            Actor_StepAnimLoop();
            if (D_80143BB0 == 0) {
                done = 1;
            }
        }
    } else {
        if (Actor_StepAnimOnce() & BYTE_MASK) {
            done = 1;
        }
    }
    if (done & BYTE_MASK) {
        g_Task->unk_2B                            = 0;
        g_Game.current->u.field.mode_12B.u8_value = 0;
    }
}
