/* Chooses a direction and requests its script. Check every including image after changes. */
MATCH void Char_TurnAndRequestScript(void) {
    u8 direction;

    direction = g_SpadWork->direction_08;
    if (!(direction & 1)) {
        g_SpadWork->direction_08 = (direction - 1) & 7;
        if (!(PLCHAR_CHECK_FACING() & 0xFF)) {
            g_SpadWork->direction_08 = (g_SpadWork->direction_08 + 2) & 7;
            if (!(PLCHAR_CHECK_FACING() & 0xFF)) {
                g_SpadWork->direction_08 = (g_SpadWork->direction_08 - 2) & 7;
            }
        }
    }
    PLCHAR_PREPARE_TURN();
    Actor_RequestScript((((s32)(g_SpadWork->direction_08 - 1) / 2) + 0x42) & 0xFF);
    g_SpadWork->unk_0B = 0;
    g_SpadWork->unk_0A = 0xB;
    g_SpadWork->unk_03 = 1;
}
