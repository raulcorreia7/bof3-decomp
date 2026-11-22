/* Runs one route step like PlChar_RunStepScript, but on arrival the script byte at +0x04 decides: 0x50 begins script 0x50 with code 2, any other value is selected as the script. */
MATCH void func_801CE628(void) {
    if (TASK(Actor)->direction == TASK(Actor)->unk_03) {
        if (TASK(Actor)->unk_04 == 0x50) {
            Script_Begin(0x50, 2);
        } else {
            Script_Select(TASK(Actor)->unk_04);
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
