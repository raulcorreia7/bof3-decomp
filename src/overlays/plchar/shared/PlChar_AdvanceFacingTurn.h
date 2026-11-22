/* Requests the facing-completion script (0x41 when the requested facing is back, 0x40 when it is away) once the work direction byte matches the target at byte 0x03, and advances the handler index; until then counts the timer at byte 0x09 down and, at zero, reloads it with 2, steps the direction byte by the work byte 0x0B wrapped to 8 bits, and requests that direction's script. */
/* func_801CFA34 (plp025), func_801CED0C (plp257), func_801CF23C (plp056), func_801CF610 (plp015) */
MATCH void PlChar_AdvanceFacingTurn(void) {
    if (TASK(Actor)->direction == TASK(Actor)->unk_03) {
        switch (TASK(Actor)->direction) {
            case FACING_DOWN:
                Script_Request(0x41);
                break;
            case FACING_RIGHT:
                Script_Request(0x40);
                break;
        }
        TASK(Actor)->header.step++;
    } else {
        TASK(Actor)->timer--;
        if (TASK(Actor)->timer == 0) {
            TASK(Actor)->timer     = 2;
            TASK(Actor)->direction = TASK(Actor)->direction + TASK(Actor)->param.turn_delta;
            TASK(Actor)->direction &= 7;
            Script_Request(TASK(Actor)->direction);
        }
    }
}
