/* Starts the character turn on the script its scenario flag and party order select: stores facing 3 or 5 at byte 0x03, its Actor_GetTurnStep sign in param.turn_step, arms the step timer and advances the task state. */
MATCH void func_801CE448(void) {
    s32 direction;

    if (SYS_TestFlag(&g_SceneFlagWords[8], 0x16)) {
        if (Party_CountOrder(0) == 1 && !(g_GameRequestFlags & 0x40)) {
            g_Task->unk_04 = 0x50;
        } else {
            g_Task->unk_04 = 0x40;
        }
    } else {
        g_Task->unk_04 = 0x41;
    }
    switch (g_Task->unk_04) {
        case 0x50:
            direction = g_Task->direction_08;
            if (abs(direction - 5) > abs(direction - 3)) {
                g_Task->param.turn_step = Actor_GetTurnStep(3);
                g_Task->unk_03          = 3;
            } else {
                g_Task->param.turn_step = Actor_GetTurnStep(5);
                g_Task->unk_03          = 5;
                g_Task->unk_04          = 0x52;
            }
            break;
        case 0x40:
            g_Task->param.turn_step = Actor_GetTurnStep(3);
            g_Task->unk_03          = 3;
            break;
        case 0x41:
            g_Task->param.turn_step = Actor_GetTurnStep(5);
            g_Task->unk_03          = 5;
            break;
    }
    g_Task->timer = 2;
    g_Task->header.step++;
}
