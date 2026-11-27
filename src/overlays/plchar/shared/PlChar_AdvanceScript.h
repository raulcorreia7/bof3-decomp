/* Advances the character's script phase: the work byte at +0x0B selects idle (0), the select-and-advance step (1) or the finished-scene check (anything else). A done flag clears the work marker at +0x2B and the panel mode byte in the game state record. */
MATCH void PlChar_AdvanceScript(void) {
    u8 done;

    done = 0;
    if (SELF(Actor)->param.unk_0B != 0) {
        if (SELF(Actor)->param.unk_0B == 1) {
            if (Script_AnimStepOnce() & BYTE_MASK) {
                Script_Select(SELF(Actor)->direction);
                SELF(Actor)->param.unk_0B = 2;
            }
        } else {
            Script_AnimStepLoop();
            if (g_GameStateIndex == 0) {
                done = 1;
            }
        }
    } else {
        if (Script_AnimStepOnce() & BYTE_MASK) {
            done = 1;
        }
    }
    if (done & BYTE_MASK) {
        SELF(Actor)->unk_2B                         = 0;
        g_Game.current->u.field.mode.unsigned_value = 0;
    }
}
