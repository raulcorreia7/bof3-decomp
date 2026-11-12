#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

MATCH void func_801EEE7C(void) {
    if (g_Task->param.unk_0B == 7) {
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EEEC0);

MATCH void func_801EF03C(void) {
    if (g_Task->param.unk_0B == 7) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF09C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0E0(void) {
    SYS_DISPATCH_BYTE(D_801F08F0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFA54();
        func_801EFE34();
        func_801EFB2C();
        func_801EF370();
        PopMatrix();
    }
}

MATCH void func_801EF178(void) {
    s32 cue;
    u8  timer_next;

    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        cue = 0x100;
        if (g_Task->param.unk_0B & 0x1) {
            cue = 0x101;
        }
        SND_QueueSelectionFx(cue);
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF27C(void) {
    u8 count;

    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyMember* work;
    PartyMember* active;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 + 1;
    if (work->unk_09 == 0x18) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = g_Task->param.unk_0B;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF370);

MATCH void func_801EFA54(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (g_Task->slot == 12) {
        rot.vz = (g_FrameCount & 0xF) << 8;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EFB2C);

INCLUDE_ASM(func_801EFE34);

MATCH void func_801F020C(void) {
    GFX_AddDitheredDrawMode(4, getTPage(0, 1, 320, 256));
    SYS_DISPATCH_BYTE(D_801F0900, g_Task->header.step);
    GFX_AddDitheredDrawMode(4, getTPage(0, 1, 320, 256));
}

MATCH void func_801F02F4(void) {
    PartyMember* work;

    work = g_Task;
    if (work->timer == 0) {
        work->unk_09 = 8;
        COORD_INT(work->pos.z) += 512;
        BMagic_NextStep();
    } else {
        work->timer = work->timer - 1;
    }
}

MATCH void func_801F034C(void) {
    PartyMember* work;
    u8           next;

    func_801EFA54();
    func_801F03C4();
    PopMatrix();
    work = g_Task;
    next = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 64;
    work->unk_09 = next;
    if (next == 0) {
        g_BattleEffectBattler->param.unk_0B = g_Task->param.unk_0B;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F03C4);
