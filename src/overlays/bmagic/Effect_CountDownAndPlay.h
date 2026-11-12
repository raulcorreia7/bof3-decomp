/* Counts the effect timer (work byte 0x09) down; at zero it plays the effect the target selector chose and raises the effect-playing flag. */
/* func_801EF0EC (magic054), func_801EF3D4 (magic113), func_801EF0BC (magic114) */
MATCH void Effect_CountDownAndPlay(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}
