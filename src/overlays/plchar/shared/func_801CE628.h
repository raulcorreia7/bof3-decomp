/* Runs one route step like PlChar_RunStepScript, but on arrival the script byte at +0x04 decides: 0x50 begins script 0x50 with code 2, any other value is selected as the script. */
MATCH void func_801CE628(void) {
    if (SELF(Actor)->direction == SELF(Actor)->unk_03) {
        if (SELF(Actor)->unk_04 == 0x50) {
            Script_Begin(0x50, 2);
        } else {
            Script_Select(SELF(Actor)->unk_04);
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
