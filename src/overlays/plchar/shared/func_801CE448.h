/* Starts the character turn on the script its scenario flag and party order select: stores facing 3 or 5 at byte 0x03, its Actor_GetTurnStep sign in param.turn_delta, arms the step timer and advances the task state. */
/* func_801CE448 (plp012, plp015, plp016, plp025, plp026, plp034, plp056) */
MATCH void func_801CE448(void) {
    s32 direction;

    if (SYS_TestFlag(g_SceneFlagRows[1], 0x16)) {
        if (Party_CountOrder(PARTY_ORDER_FIELD) == 1 && !(g_GameRequestFlags & AREA_LOAD_FLAG_SHOP)) {
            TASK(Actor)->unk_04 = 0x50;
        } else {
            TASK(Actor)->unk_04 = 0x40;
        }
    } else {
        TASK(Actor)->unk_04 = 0x41;
    }
    switch (TASK(Actor)->unk_04) {
        case 0x50:
            direction = TASK(Actor)->direction;
            if (abs(direction - FACING_DOWN) > abs(direction - FACING_RIGHT)) {
                TASK(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_RIGHT);
                TASK(Actor)->unk_03           = FACING_RIGHT;
            } else {
                TASK(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_DOWN);
                TASK(Actor)->unk_03           = FACING_DOWN;
                TASK(Actor)->unk_04           = 0x52;
            }
            break;
        case 0x40:
            TASK(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_RIGHT);
            TASK(Actor)->unk_03           = FACING_RIGHT;
            break;
        case 0x41:
            TASK(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_DOWN);
            TASK(Actor)->unk_03           = FACING_DOWN;
            break;
    }
    TASK(Actor)->timer = 2;
    TASK(Actor)->header.step++;
}
