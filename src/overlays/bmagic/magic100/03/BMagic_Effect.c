#include "magic100_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EEC70(void) {
    PartyMember* src;
    PartyMember* work;
    u32          slot;
    u32          counter;
    u32          value;
    s32          span;

    src                  = BATTLE_ACTIVE_WORK;
    g_Task->facing       = src->facing;
    g_Task->pos.x.fixed  = src->pos.x.fixed;
    g_Task->pos.y.fixed  = src->pos.y.fixed;
    span                 = g_Battle.selected_actor->pos.z.fixed;
    g_Task->unk_09       = 0;
    g_Task->pos.z.fixed  = span;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot    = Battle_AllocEffect(1, 0xA) & BYTE_MASK;
    counter = 0;
    value   = 1;
    do {
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = counter;
        g_BattleEffects[slot].arg.unk_09   = value;
        work                               = g_Task;
        g_BattleEffects[slot].target.party = work;
        work->param.unk_0B += 1;
        counter += 1;
        value += 2;
    } while (counter < 8);
    SND_QueueSelectionFx(0x100);
}
#else
INCLUDE_ASM(func_801EEC70);
#endif

MATCH void func_801EED9C(void) {
    if (g_Task->unk_09 != 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE58 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(D_801EFDD0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF434();
        func_801EF4E8();
        PopMatrix();
        func_801EF8E8();
        func_801EF9D4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF3C);

MATCH void func_801EF0D8(void) {
    u32          slot;
    PartyMember* battler;
    u8           timer;

    slot = LOBU(g_Battle.target_selector);
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    if (g_Task->param.unk_0B & 1) {
        g_Task->unk_20 = (g_Task->unk_20 + 0x200) & 0xFFF;
    } else {
        g_Task->unk_20 = (g_Task->unk_20 - 0x200) & 0xFFF;
    }
    g_Task->unk_14 = func_800AF4A0(battler, 0xC000, g_Task->unk_18 << 6);
    timer          = g_Task->timer + 4;
    g_Task->timer  = timer;
    if (timer == 0x10) {
        g_Task->header.step++;
    }
}

INCLUDE_ASM(func_801EF1DC);

INCLUDE_ASM(func_801EF358);

MATCH void func_801EF434(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(COORD_INT(g_Task->pos.z) + 0x100) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801EF4E8);

#ifdef NON_MATCHING
NON_MATCHING void func_801EF8E8(void) {
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;
    s32          height;
    PartyMember* work;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (work->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (work->pos.y.fixed >> 9) - 0x4000;
    if (work->header.step < 3) {
        height = -COORD_INT(work->pos.z);
    } else {
        height = -(s16)Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    }
    pos.vz = height / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}
#else
INCLUDE_ASM(func_801EF8E8);
#endif

INCLUDE_ASM(func_801EF9D4);
