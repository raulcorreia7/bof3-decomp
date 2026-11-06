/* Runs one route step like Char_RunStepScript, but on arrival the script
 * byte at +0x04 decides: 0x50 begins script 0x50 with code 2, any other value
 * is selected as the script. One definition shared by the plchar character
 * programs; every change here must verify every member image. */
MATCH void func_801CE628(void) {
    if (g_Task->direction_08 == g_Task->unk_03) {
        if (g_Task->unk_04 == 0x50) {
            Actor_BeginScript(0x50, 2);
        } else {
            Actor_SelectScript(g_Task->unk_04);
        }
        g_Task->header.step++;
    } else {
        g_Task->unk_09--;
        if (g_Task->unk_09 == 0) {
            g_Task->unk_09       = 2;
            g_Task->direction_08 = g_Task->direction_08 + g_Task->unk_0B;
            g_Task->direction_08 &= 7;
            Actor_RequestScript(g_Task->direction_08);
        }
    }
}
