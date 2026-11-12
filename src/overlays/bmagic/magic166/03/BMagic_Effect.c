#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_PlayOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EF724[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EF724[i];
            g_BattleEffectBattler = D_801EF724[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

#include "overlays/bmagic/func_801EED04.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF71C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF284();
        func_801EF380();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

INCLUDE_ASM(func_801EF138);

#include "overlays/bmagic/BMagic_SetupEffectMatrix.h"

MATCH void func_801EF284(void) {
    BMAGIC_SETUP_EFFECT_MATRIX();
}

INCLUDE_ASM(func_801EF380);

/* func_801EF69C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
