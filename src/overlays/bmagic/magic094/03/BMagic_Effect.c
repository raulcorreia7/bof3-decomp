#include "magic094_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED60);
}

MATCH void func_801EEC5C(void) {
    PartyMember* actor;
    u32          effect_slot;

    actor                                     = g_Battle.selected_actor;
    g_Task->pos.x.fixed                       = actor->pos.x.fixed;
    g_Task->pos.y.fixed                       = actor->pos.y.fixed;
    g_Task->pos.z.fixed                       = actor->pos.z.fixed;
    g_Task->unk_2E.half                       = actor->unk_2E.half;
    g_Task->unk_30.half                       = actor->unk_30.half - 16;
    effect_slot                               = Battle_AllocEffect(1, 21) & BYTE_MASK;
    g_BattleEffects[effect_slot].target.party = g_Task;
    g_BattleEffects[effect_slot].unk_08       = actor->facing;
    g_BattleEffects[effect_slot].pos.x.fixed  = actor->pos.x.fixed;
    g_BattleEffects[effect_slot].pos.y.fixed  = actor->pos.y.fixed;
    g_BattleEffects[effect_slot].pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B                      = 0;
    g_Task->header.mode++;
    SND_QueueSelectionFx(0x100);
}

/* Copies the selected actor's unk_2E and unk_30 - 0x10; at unk_0B 0xFF releases the target and plays. */
MATCH void func_801EED60(void) {
    u32          slot;
    u8*          selector;
    PartyMember* battler;

    g_Task->unk_2E.half = g_BattleSelectedActor->unk_2E.half;
    g_Task->unk_30.half = g_BattleSelectedActor->unk_30.half - 0x10;
    if (g_Task->param.unk_0B == 0xFF) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

MATCH void func_801EEE4C(void) {
    SYS_DISPATCH_BYTE(D_801EF988, g_Task->header.mode);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        func_801EF654();
        func_801EF14C();
        func_801EF710();
        PopMatrix();
    }
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
}

MATCH void func_801EEF1C(void) {
    Battle_ApplyDamageFlags(g_Battle.target_selector, 32);
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.mode++;
}

MATCH void func_801EEF7C(void) {
    u32          slot;
    u8           step;
    PartyMember* battler;

    g_Task->timer++;
    step           = g_Task->unk_09 + 1;
    g_Task->unk_09 = step;
    if (step == 0x10) {
        slot = LOBU(g_Battle.target_selector);
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            battler = &g_Game.members[slot];
        } else {
            battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        func_80196718(battler);
        func_8019651C(battler, 6, 4, 8, 0);
        g_Task->unk_09 = 0;
        g_Task->header.mode++;
    }
}

MATCH void func_801EF078(void) {
    u8 timer;
    u8 count;

    timer = g_Task->timer;
    if (timer < 16U) {
        g_Task->timer = timer + 1;
    }
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->unk_09 = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF0FC(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x20) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF14C);

MATCH void func_801EF654(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_Task->timer << 4;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF710);
