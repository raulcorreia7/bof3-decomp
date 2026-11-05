/* Advances the script after staging the palette. Check every including image after changes. */
MATCH void Char_AdvancePaletteScript(void) {
    u8 done;
    u8 state;

    done = 0;
    if (g_SpadWork->unk_0B == 1) {
        GFX_StagePalette((g_SpadWork->unk_05 << 6) + 0x80035600, 0);
        g_SpadWork->unk_0B = 2;
    }
    state = g_SpadWork->unk_0B;
    if (state != 0) {
        if (state == 2) {
            if (func_8014DAEC() & 0xFF) {
                Actor_SelectScript(g_SpadWork->direction_08);
                g_SpadWork->unk_0B = 3;
            }
        } else {
            func_8014D978();
        }
        if (g_GameStateIndex == 0) {
            done = 1;
        }
    } else if (func_8014DAEC() & 0xFF) {
        done = 1;
    }
    if (done & 0xFF) {
        g_SpadWork->unk_2B             = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
}
