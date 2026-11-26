/* Requests the facing-completion script (0x41 when the requested facing is back, 0x40 when it is away) once the work direction byte matches the target at byte 0x03, and advances the handler index; until then counts the timer at byte 0x09 down and, at zero, reloads it with 2, steps the direction byte by the work byte 0x0B wrapped to 8 bits, and requests that direction's script. */
/* func_801CFA34 (plp025), func_801CED0C (plp257), func_801CF23C (plp056), func_801CF610 (plp015) */
MATCH void PlChar_AdvanceFacingTurn(void) {
    if (SELF(Actor)->direction == SELF(Actor)->unk_03) {
        switch (SELF(Actor)->direction) {
            case FACING_DOWN:
                Script_Request(0x41);
                break;
            case FACING_RIGHT:
                Script_Request(0x40);
                break;
        }
        SELF(Actor)->header.step++;
    } else {
        SELF(Actor)->timer--;
        if (SELF(Actor)->timer == 0) {
            SELF(Actor)->timer     = 2;
            SELF(Actor)->direction = SELF(Actor)->direction + SELF(Actor)->param.turn_delta;
            SELF(Actor)->direction &= 7;
            Script_Request(SELF(Actor)->direction);
        }
    }
}
