/* Advances the script after staging the palette. Check every including image after changes. */
MATCH void PlChar_AdvancePaletteScript(void) {
    u8 done;
    u8 state;

    done = 0;
    if (TASK(Actor)->param.unk_0B == 1) {
        GFX_PaletteLoad((TASK(Actor)->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
        TASK(Actor)->param.unk_0B = 2;
    }
    state = TASK(Actor)->param.unk_0B;
    if (state != 0) {
        if (state == 2) {
            if (Script_AnimStepOnce() & 0xFF) {
                Script_Select(TASK(Actor)->direction);
                TASK(Actor)->param.unk_0B = 3;
            }
        } else {
            Script_AnimStepLoop();
        }
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            done = 1;
        }
    } else if (Script_AnimStepOnce() & 0xFF) {
        done = 1;
    }
    if (done & 0xFF) {
        TASK(Actor)->unk_2B                = 0;
        g_Game.current->u.field.mode.value = 0;
    }
}
