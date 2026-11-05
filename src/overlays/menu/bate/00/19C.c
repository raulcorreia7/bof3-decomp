#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The bate overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D9C(void) {
    SYS_DISPATCH_BYTE(D_801D86E0, D_80148650);
}

MATCH void func_801D0DD8(void) {
    D_80148651 = 0;
    D_80148652 = 0;
    D_80148650 = D_8018E244 + 2;
}

MATCH void func_801D0E04(void) {
    u16* count;

    Menu_ResetPanelTasks();
    count = &g_GameEntrySubstate;
    *count += 1;
}

MATCH void func_801D0E38(void) {
    SYS_DISPATCH_BYTE(D_801D8700, D_80148651);
}

MATCH void func_801D0E74(void) {
    SYS_DISPATCH_BYTE(D_801D870C, D_80148652);
}

MATCH void func_801D0EB0(void) {
    u8* count;

    UI_SetMode(3);
    count = &D_80148652;
    *count += 1;
}

INCLUDE_ASM(func_801D0EE4);

MATCH void func_801D0F70(void) {
    u8* timer;

    Menu_DrawClutStrip(D_80144953);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        D_801D8ED4.unk_00 = 0;
        D_801D8ED4.unk_04 = 1;
        D_801D8ED4.unk_08 = 0;
        D_80148652        = 0;
        D_80148659        = 0;
        D_80148651 += 1;
    }
}

INCLUDE_ASM(func_801D0FF8);

INCLUDE_ASM(func_801D1044);
