/* Requests the facing-completion script (0x41 when the requested facing is back, 0x40 when it is away) once the work direction byte matches the target at byte 0x03. */
/* func_801CFA34 (plp025), func_801CED0C (plp257), func_801CF23C (plp056), func_801CF610 (plp015) */
MATCH void Char_AdvanceFacingTurn(void) {
    if (g_Task->direction_08 == g_Task->unk_03) {
        switch (g_Task->direction_08) {
            case FACING_DOWN:
                Actor_RequestScript(0x41);
                break;
            case FACING_RIGHT:
                Actor_RequestScript(0x40);
                break;
        }
        g_Task->header.step++;
    } else {
        g_Task->timer--;
        if (g_Task->timer == 0) {
            g_Task->timer        = 2;
            g_Task->direction_08 = g_Task->direction_08 + g_Task->param.turn_step;
            g_Task->direction_08 &= 7;
            Actor_RequestScript(g_Task->direction_08);
        }
    }
}
