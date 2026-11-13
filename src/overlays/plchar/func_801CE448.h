/* Starts the character turn on the script its scenario flag and party order select: stores facing 3 or 5 at byte 0x03, its Actor_GetTurnStep sign in param.turn_step, arms the step timer and advances the task state. */
/* func_801CE448 (plp012, plp015, plp016, plp025, plp026, plp034, plp056) */
MATCH void func_801CE448(void) {
    s32 direction;

    if (SYS_TestFlag(&g_SceneFlagWords[8], 0x16)) {
        if (Party_CountOrder(PARTY_ORDER_FIELD) == 1 && !(g_GameRequestFlags & AREA_LOAD_FLAG_SHOP)) {
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
            if (abs(direction - FACING_DOWN) > abs(direction - FACING_RIGHT)) {
                g_Task->param.turn_step = Actor_GetTurnStep(FACING_RIGHT);
                g_Task->unk_03          = FACING_RIGHT;
            } else {
                g_Task->param.turn_step = Actor_GetTurnStep(FACING_DOWN);
                g_Task->unk_03          = FACING_DOWN;
                g_Task->unk_04          = 0x52;
            }
            break;
        case 0x40:
            g_Task->param.turn_step = Actor_GetTurnStep(FACING_RIGHT);
            g_Task->unk_03          = FACING_RIGHT;
            break;
        case 0x41:
            g_Task->param.turn_step = Actor_GetTurnStep(FACING_DOWN);
            g_Task->unk_03          = FACING_DOWN;
            break;
    }
    g_Task->timer = 2;
    g_Task->header.step++;
}
