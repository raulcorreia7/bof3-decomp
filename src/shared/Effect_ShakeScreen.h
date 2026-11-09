/* Sets the three screen shake offsets from the effect ticker and counts the effect down. */
/* func_800A8EB8 (battle), func_800C26A4 (boss033) */
MATCH void Effect_ShakeScreen(void) {
    {
        PartyMember* work;

        work         = (PartyMember*)g_Task;
        work->unk_5D = -(work->param.unk_0B * 16);
        work         = (PartyMember*)g_Task;
        work->unk_5F = -(work->param.unk_0B * 16);
        work         = (PartyMember*)g_Task;
        work->unk_5E = -(work->param.unk_0B * 16);
    }
    Actor_StepAnimOnce();
    {
        PartyMember* work;
        u8           old;

        work         = (PartyMember*)g_Task;
        old          = work->unk_09;
        work->unk_09 = old + 255;
        if (old == 0) {
            func_801E5988();
        }
    }
}
