/* Runs one route step like PlChar_RunStepScript, but on arrival the script byte at +0x04 decides: 0x50 begins script 0x50 with code 2, any other value is selected as the script. */
MATCH void func_801CE628(void) {
    if (g_Task->direction == g_Task->unk_03) {
        if (g_Task->unk_04 == 0x50) {
            Script_Begin(0x50, 2);
        } else {
            Script_Select(g_Task->unk_04);
        }
        g_Task->header.step++;
    } else {
        g_Task->timer--;
        if (g_Task->timer == 0) {
            g_Task->timer     = 2;
            g_Task->direction = g_Task->direction + g_Task->param.turn_step;
            g_Task->direction &= 7;
            Script_Request(g_Task->direction);
        }
    }
}
