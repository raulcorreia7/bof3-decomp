#include "engine/slus/slus.h"

/* dispatches the selection byte D_801490BC.step_id through the handler table at 0x34 of the current g_AreaLoads bank
 * record (ids below 0x80) or Message_DispatchBankStep, then sets owner mode 3: a pending area request latches mode 1 and
 * advances g_UiWindowStep, a cleared one latches 7; clears D_801490B8.
 */
MATCH void Message_DispatchAnswerStep(void) {
    u8 id;

    id = D_801490BC.step_id;
    if (id < 0x80u) {
        ((AreaLoad*)g_AreaLoads[g_GameAreaId])->steps[id]();
    } else {
        Message_DispatchBankStep();
    }

    D_80148357 = 3;
    if (g_MessageRequest != 0xFFFF) {
        D_80148333[0]  = 1;
        g_UiWindowStep = g_UiWindowStep + 1;
    } else {
        g_UiWindowStep = 7;
    }
    D_801490B8[0] = 0;
}
