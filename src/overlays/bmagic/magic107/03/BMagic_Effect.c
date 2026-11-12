#include "magic107_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED40);
}

/* The g_Task base for the span read must be fetched before the D_801EC364 store and the
 * z member read kept in place; both inline reads or an early span local shift the reload. */
MATCH void func_801EEC5C(void) {
    PartyMember* work;
    s32          scroll_x;
    u32          offset;

    Battle_CenterCamera();
    offset                                  = (Battle_AllocEffect(1, 0x19) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
    FIELD(PartyMember*, D_801EC3A4, offset) = g_Task;
    FIELD(u8, D_801EC338, offset)           = ((PartyMember*)D_8014637C)->facing;
    scroll_x                                = g_AreaScrollTargetX;
    work                                    = g_Task;
    FIELD(s32, D_801EC364, offset)          = scroll_x;
    FIELD(s32, D_801EC368, offset)          = g_AreaScrollTargetY;
    FIELD(s32, D_801EC36C, offset)          = work->pos.z.fixed + 0x04000000;
    SND_QueueSelectionFx(0x100);
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEDA0(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_Task->header.mode);
    if (g_Task->header.flags != 0) {
        func_801EEFD4();
        func_801EF0E4();
        func_801EF544();
        func_801EF290();
        PopMatrix();
        Effect_SetActorMatrixQuarterRoll();
        func_801F01AC();
        func_801EFAE0();
        func_801EFEA8();
        PopMatrix();
    }
}

MATCH void func_801EEE50(void) {
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.mode++;
}

MATCH void func_801EEEA0(void) {
    g_Task->unk_09 += 1;
    g_Task->timer += 1;
    if (g_Task->unk_09 == 0x20) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_AdvanceOnTick.h"

MATCH void func_801EEF5C(void) {
    PartyMember* active;

    g_Task->unk_09 = g_Task->unk_09 + 1;
    g_Task->timer  = g_Task->timer - 1;
    if (g_Task->timer == 0) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = 255;
        func_801E5988();
    }
}

MATCH void func_801EEFD4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      angle;

    PushMatrix();
    if (g_Task->facing & 1) {
        rot.vx = 0;
        angle  = g_Task->unk_09 & 0x3F;
        rot.vy = (u32)rsin(angle << 6) >> 3;
        rot.vz = 0;
    } else {
        angle  = g_Task->unk_09 & 0x3F;
        rot.vx = (u32)rsin(angle << 6) >> 3;
        rot.vy = 0;
        rot.vz = 0;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF0E4);

INCLUDE_ASM(func_801EF290);

INCLUDE_ASM(func_801EF544);

#include "overlays/bmagic/Effect_SetActorMatrixQuarterRoll.h"

INCLUDE_ASM(func_801EFAE0);

INCLUDE_ASM(func_801EFEA8);

INCLUDE_ASM(func_801F01AC);
